#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ rdrand_available; } ;
struct TYPE_3__ {int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rdrand32_step (unsigned int*) ; 
 int crypto_stream_chacha20_KEYBYTES ; 
 TYPE_2__ global ; 
 TYPE_1__ stream ; 

__attribute__((used)) static void
randombytes_internal_random_xorhwrand(void)
{
/* LCOV_EXCL_START */
#ifdef HAVE_RDRAND
    unsigned int r;

    if (global.rdrand_available == 0) {
        return;
    }
    (void) _rdrand32_step(&r);
    * (uint32_t *) (void *)
        &stream.key[crypto_stream_chacha20_KEYBYTES - 4] ^= (uint32_t) r;
#endif
/* LCOV_EXCL_STOP */
}