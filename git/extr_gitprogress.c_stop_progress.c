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
struct progress {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  finish_if_sparse (struct progress*) ; 
 int /*<<< orphan*/  stop_progress_msg (struct progress**,int /*<<< orphan*/ ) ; 

void stop_progress(struct progress **p_progress)
{
	finish_if_sparse(*p_progress);

	stop_progress_msg(p_progress, _("done"));
}