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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {TYPE_2__ w_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCSH_I_SEEK ; 
 int /*<<< orphan*/  TC_BREAK ; 
 int /*<<< orphan*/  btell (TYPE_2__*) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int /*<<< orphan*/  pintr_push_enable (int*) ; 
 int /*<<< orphan*/  search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setintr ; 
 TYPE_1__* whyles ; 

__attribute__((used)) static void
preread(void)
{
    int old_pintr_disabled;

    whyles->w_end.type = TCSH_I_SEEK;
    if (setintr)
	pintr_push_enable(&old_pintr_disabled);
    search(TC_BREAK, 0, NULL);		/* read the expression in */
    if (setintr)
	cleanup_until(&old_pintr_disabled);
    btell(&whyles->w_end);
}