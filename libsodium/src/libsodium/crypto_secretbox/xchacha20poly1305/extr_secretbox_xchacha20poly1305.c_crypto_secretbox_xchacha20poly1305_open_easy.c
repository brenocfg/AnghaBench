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
 unsigned long long crypto_secretbox_xchacha20poly1305_MACBYTES ; 
 int crypto_secretbox_xchacha20poly1305_open_detached (unsigned char*,unsigned char const*,unsigned char const*,unsigned long long,unsigned char const*,unsigned char const*) ; 

int
crypto_secretbox_xchacha20poly1305_open_easy(unsigned char *m,
                                             const unsigned char *c,
                                             unsigned long long clen,
                                             const unsigned char *n,
                                             const unsigned char *k)
{
    if (clen < crypto_secretbox_xchacha20poly1305_MACBYTES) {
        return -1;
    }
    return crypto_secretbox_xchacha20poly1305_open_detached
        (m, c + crypto_secretbox_xchacha20poly1305_MACBYTES, c,
         clen - crypto_secretbox_xchacha20poly1305_MACBYTES, n, k);
}