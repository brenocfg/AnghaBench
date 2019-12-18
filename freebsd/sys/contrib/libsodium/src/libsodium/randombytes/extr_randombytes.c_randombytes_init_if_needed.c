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
 int /*<<< orphan*/ * RANDOMBYTES_DEFAULT_IMPLEMENTATION ; 
 int /*<<< orphan*/ * implementation ; 
 int /*<<< orphan*/  randombytes_stir () ; 

__attribute__((used)) static void
randombytes_init_if_needed(void)
{
    if (implementation == NULL) {
        implementation = RANDOMBYTES_DEFAULT_IMPLEMENTATION;
        randombytes_stir();
    }
}