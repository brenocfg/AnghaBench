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

/* Variables and functions */
 int crypto_secretbox_xchacha20poly1305_detached (unsigned char*,unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,unsigned char const*) ; 

int
crypto_box_curve25519xchacha20poly1305_detached_afternm(
    unsigned char *c, unsigned char *mac, const unsigned char *m,
    unsigned long long mlen, const unsigned char *n, const unsigned char *k)
{
    return crypto_secretbox_xchacha20poly1305_detached(c, mac, m, mlen, n, k);
}