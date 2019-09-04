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
struct raw_message {int dummy; } ;

/* Variables and functions */
 int _rwm_encrypt_decrypt (struct raw_message*,int,struct vk_aes_ctx*,int,unsigned char*) ; 

int rwm_encrypt_decrypt_cbc (struct raw_message *raw, int bytes, struct vk_aes_ctx *ctx, unsigned char iv[16]) {
  return _rwm_encrypt_decrypt (raw, bytes, ctx, 1, iv);
}