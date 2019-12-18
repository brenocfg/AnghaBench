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
struct directory {scalar_t__ di_count; struct directory* di_name; scalar_t__ di_prev; scalar_t__ di_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct directory*) ; 

void
dfree(struct directory *dp)
{

    if (dp->di_count != 0) {
	dp->di_next = dp->di_prev = 0;
    }
    else {
	xfree(dp->di_name);
	xfree(dp);
    }
}