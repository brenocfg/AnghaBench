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
struct TYPE_4__ {scalar_t__ pid; } ;
struct TYPE_3__ {scalar_t__ initialized; } ;

/* Variables and functions */
 scalar_t__ getpid () ; 
 TYPE_2__ global ; 
 int /*<<< orphan*/  randombytes_internal_random_stir () ; 
 int /*<<< orphan*/  sodium_misuse () ; 
 TYPE_1__ stream ; 

__attribute__((used)) static void
randombytes_internal_random_stir_if_needed(void)
{
#ifdef HAVE_GETPID
    if (stream.initialized == 0) {
        randombytes_internal_random_stir();
    } else if (global.pid != getpid()) {
        sodium_misuse(); /* LCOV_EXCL_LINE */
    }
#else
    if (stream.initialized == 0) {
        randombytes_internal_random_stir();
    }
#endif
}