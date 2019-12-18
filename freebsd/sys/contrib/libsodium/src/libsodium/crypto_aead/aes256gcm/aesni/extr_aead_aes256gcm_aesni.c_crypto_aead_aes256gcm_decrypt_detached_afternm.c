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
typedef  int /*<<< orphan*/  crypto_aead_aes256gcm_state ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 

int
crypto_aead_aes256gcm_decrypt_detached_afternm(unsigned char *m, unsigned char *nsec,
                                               const unsigned char *c, unsigned long long clen,
                                               const unsigned char *mac,
                                               const unsigned char *ad, unsigned long long adlen,
                                               const unsigned char *npub,
                                               const crypto_aead_aes256gcm_state *ctx_)
{
    errno = ENOSYS;
    return -1;
}