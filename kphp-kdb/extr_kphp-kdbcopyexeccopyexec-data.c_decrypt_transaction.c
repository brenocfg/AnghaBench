#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int dummy; } ;
struct lev_copyexec_aux_transaction_header {int transaction_id; long long binlog_pos; scalar_t__ size; } ;
struct lev_copyexec_aux_transaction_footer {int /*<<< orphan*/  sha1; } ;

/* Variables and functions */
 int COPYEXEC_ERR_ALIGN ; 
 int COPYEXEC_ERR_DECRYPT ; 
 int COPYEXEC_ERR_PUBKEY_PERMISSIONS ; 
 int COPYEXEC_ERR_SHA1 ; 
 int COPYEXEC_ERR_SIZE ; 
 int COPYEXEC_ERR_STAT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SHA1 (void*,int,unsigned char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_file_permissions (char*,struct stat*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 char* public_key_prefix ; 
 int rsa_decrypt (char*,int,unsigned char*,int,void**,int*,int) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

int decrypt_transaction (unsigned char *input, int ilen, int key_id, long long offset, int transaction_id, unsigned char **output, int *olen) {
  *output = NULL;
  *olen = -1;

  char public_key_name[PATH_MAX];
  assert (snprintf (public_key_name, PATH_MAX, "%s%d", public_key_prefix, key_id) < PATH_MAX);

  struct stat st;
  if (stat (public_key_name, &st) < 0) {
    vkprintf (3, "stat (\"%s\") failed. %m\n", public_key_name);
    return COPYEXEC_ERR_STAT;
  }

  if (check_file_permissions (public_key_name, &st, 3) < 0) {
    return COPYEXEC_ERR_PUBKEY_PERMISSIONS;
  }

  void *b;
  int blen;
  int r = rsa_decrypt (public_key_name, 1, input, ilen, &b, &blen, 1);

  if (r < 0) {
    kprintf ("rsa_decrypt returns error code %d.\n", r);
    return COPYEXEC_ERR_DECRYPT;
  }

  if (blen & 3) {
    kprintf ("decrypted transaction len isn't aligned.\n");
    return COPYEXEC_ERR_ALIGN;
  }

  struct lev_copyexec_aux_transaction_header *B = b;
  if (blen < (int) (sizeof (struct lev_copyexec_aux_transaction_header) + sizeof (struct lev_copyexec_aux_transaction_footer))) {
    free (b);
    kprintf ("decrypted transaction len too short.\n");
    return COPYEXEC_ERR_SIZE;
  }

  if ((int) B->size != blen) {
    free (b);
    kprintf ("rsa_decrypted olen didn't match to transaction header size field (position: %lld).\n", offset);
    return COPYEXEC_ERR_DECRYPT;
  }

  if (B->transaction_id != transaction_id) {
    free (b);
    kprintf ("transaction_id didn't match, expected %d. (position: %lld).\n", transaction_id, offset);
    return COPYEXEC_ERR_DECRYPT;
  }

  if (B->binlog_pos != offset) {
    free (b);
    kprintf ("transaction pos didn't match (position: %lld).\n", offset);
    return COPYEXEC_ERR_DECRYPT;
  }
  struct lev_copyexec_aux_transaction_footer *C = b + blen - 20;

  unsigned char decrypted_sha[20];
  SHA1 (b, blen - 20, decrypted_sha);
  if (memcmp (decrypted_sha, C->sha1, 20)) {
    free (b);
    kprintf ("transaction sha1 didn't match (position: %lld).\n", offset);
    return COPYEXEC_ERR_SHA1;
  }
  *output = b;
  *olen = blen;
  return 0;
}