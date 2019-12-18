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
struct directory {struct directory* di_next; struct directory* di_prev; } ;

/* Variables and functions */
 struct directory* dcwd ; 

__attribute__((used)) static void
dextract(struct directory *dp)
{
    if (dp == dcwd)
	return;
    dp->di_next->di_prev = dp->di_prev;
    dp->di_prev->di_next = dp->di_next;
    dp->di_next = dcwd->di_next;
    dp->di_prev = dcwd;
    dp->di_next->di_prev = dp;
    dcwd->di_next = dp;
}