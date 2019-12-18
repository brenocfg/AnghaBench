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
struct xferstat {int /*<<< orphan*/  rcvd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  stat_display (struct xferstat*,int /*<<< orphan*/ ) ; 
 scalar_t__ v_progress ; 

__attribute__((used)) static void
stat_update(struct xferstat *xs, off_t rcvd)
{

	xs->rcvd = rcvd;
	if (v_progress)
		stat_display(xs, 0);
}