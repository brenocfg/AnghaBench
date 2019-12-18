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
struct whyle {struct whyle* w_fename; scalar_t__ w_fe0; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkfree (scalar_t__) ; 
 int /*<<< orphan*/  xfree (struct whyle*) ; 

__attribute__((used)) static void
wpfree(struct whyle *wp)
{
	if (wp->w_fe0)
	    blkfree(wp->w_fe0);
	xfree(wp->w_fename);
	xfree(wp);
}