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
typedef  void* gcry_cipher_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  gcry_cipher_close (void*) ; 

void aes_encrypt_deinit(void *ctx)
{
	gcry_cipher_hd_t hd = ctx;
	gcry_cipher_close(hd);
}