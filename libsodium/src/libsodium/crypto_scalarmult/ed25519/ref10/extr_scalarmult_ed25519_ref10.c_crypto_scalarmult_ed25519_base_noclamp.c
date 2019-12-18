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
 int _crypto_scalarmult_ed25519_base (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 

int
crypto_scalarmult_ed25519_base_noclamp(unsigned char *q,
                                       const unsigned char *n)
{
    return _crypto_scalarmult_ed25519_base(q, n, 0);
}