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
struct random_gather_extra {int bytes; int limit; scalar_t__ hex; } ;
struct gather_entry {int res_bytes; int* data; } ;
struct connection {int dummy; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int* A ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_EncryptFinal_ex (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  EVP_EncryptUpdate (int /*<<< orphan*/ *,int*,int*,char*,int) ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 char* R ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int random_merge_end_query (struct connection *c, const char *key, int key_len, void *E, struct gather_entry *data, int tot_num) {
  struct random_gather_extra *extra = E;
  int i, j, bi = 0;
  for (i = 1; i < tot_num; i++) {
    if (data[bi].res_bytes < data[i].res_bytes) {
      bi = i;
    }
  }
  int max_bytes = data[bi].res_bytes, *r, *w;
  if (max_bytes <= 64) {
    return 0;
  }
  memset (R, 0, (max_bytes + 3) & -4);

  for (i = 0; i < tot_num; i++) {
    r = data[i].data;
    w = (int *) R;
    for (j = 0; j < data[i].res_bytes; j += 4) {
      *w++ ^= *r++;
    }
  }

  EVP_CIPHER_CTX e;
  EVP_CIPHER_CTX_init (&e);
  EVP_EncryptInit_ex (&e, EVP_aes_256_cbc(), NULL, R, R + 32);
  int c_len, f_len;

  if (!EVP_EncryptUpdate (&e, A, &c_len, R + 64, max_bytes - 64)) {
    vkprintf (1, "EVP_EncryptUpdate fail.\n");
    EVP_CIPHER_CTX_cleanup (&e);
    return 0;
  }

  if (!EVP_EncryptFinal_ex (&e, A + c_len, &f_len)) {
    vkprintf (1, "EVP_EncryptFinal_ex fail.\n");
    EVP_CIPHER_CTX_cleanup (&e);
    return 0;
  }
  EVP_CIPHER_CTX_cleanup (&e);
  f_len += c_len;

  int res = f_len < data[0].res_bytes ? f_len : data[0].res_bytes;
  if (res > extra->bytes) {
    res = extra->bytes;
  }

  w = (int *) A;
  r = data[0].data;
  for (i = 0; i < res; i += 4) {
    *w++ ^= *r++;
  }

  if (extra->hex) {
    static const char hcyf[16] = "0123456789abcdef";
    for (i = 0; i < res; i++) {
      R[2*i] = hcyf[(A[i] >> 4) & 15];
      R[2*i+1] = hcyf[A[i] & 15];
    }
    res *= 2;
    if (res > extra->limit) {
      res = extra->limit;
    }
    return return_one_key (c, key, (char *) R, res);
  }
  return return_one_key (c, key, (char *) A, res);
}