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
struct vk_aes_ctx {int dummy; } ;
struct raw_message {int total_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rwm_dump (struct raw_message*) ; 
 int rwm_encrypt_decrypt (struct raw_message*,int,struct vk_aes_ctx*,unsigned char*) ; 
 int rwm_sha1 (struct raw_message*,int,unsigned char*) ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int decrypt_udp_message (struct raw_message *msg, struct vk_aes_ctx *ctx, unsigned char *key) {
  if (msg->total_bytes & 15) {
    vkprintf (1, "Length of encrypted part is not multiple of 16\n");
    return -1;
  }

  static unsigned char t[32];
  memcpy (t, key, 32);
  assert (!(msg->total_bytes & 15));
  if (verbosity >= 4) {
    rwm_dump (msg);
  }
  assert (rwm_encrypt_decrypt (msg, msg->total_bytes, ctx, key) == msg->total_bytes);

  if (verbosity >= 4) {
    rwm_dump (msg);
  }

#ifdef USE_SHA1
  static unsigned char c[20];
  assert (rwm_sha1 (msg, msg->total_bytes, c) == msg->total_bytes);
  if (memcmp (c, t, 16)) {
    vkprintf (1, "Sha1 mismatch\n");
    return -1;
  }
#endif
  return 0;
}