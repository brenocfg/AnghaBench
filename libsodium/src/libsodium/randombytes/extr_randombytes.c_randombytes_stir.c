#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* stir ) () ;} ;

/* Variables and functions */
 TYPE_1__* implementation ; 
 int /*<<< orphan*/  randombytes_init_if_needed () ; 
 int /*<<< orphan*/  stub1 () ; 

void
randombytes_stir(void)
{
    randombytes_init_if_needed();
    if (implementation->stir != NULL) {
        implementation->stir();
    }
}