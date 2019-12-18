#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; scalar_t__ f_seek; } ;
struct TYPE_4__ {TYPE_2__ w_end; } ;

/* Variables and functions */
 scalar_t__ TCSH_F_SEEK ; 
 int /*<<< orphan*/  TC_BREAK ; 
 int /*<<< orphan*/  bseek (TYPE_2__*) ; 
 int /*<<< orphan*/  btell (TYPE_2__*) ; 
 int /*<<< orphan*/  search (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wfree () ; 
 TYPE_1__* whyles ; 

__attribute__((used)) static void
toend(void)
{
    if (whyles->w_end.type == TCSH_F_SEEK && whyles->w_end.f_seek == 0) {
	search(TC_BREAK, 0, NULL);
	btell(&whyles->w_end);
	whyles->w_end.f_seek--;
    }
    else {
	bseek(&whyles->w_end);
    }
    wfree();
}