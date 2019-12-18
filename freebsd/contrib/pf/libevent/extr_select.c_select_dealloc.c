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
struct selectop {struct selectop* event_w_by_fd; struct selectop* event_r_by_fd; struct selectop* event_writeset_out; struct selectop* event_readset_out; struct selectop* event_writeset_in; struct selectop* event_readset_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct selectop*) ; 
 int /*<<< orphan*/  memset (struct selectop*,int /*<<< orphan*/ ,int) ; 

void
select_dealloc(void *arg)
{
	struct selectop *sop = arg;

	if (sop->event_readset_in)
		free(sop->event_readset_in);
	if (sop->event_writeset_in)
		free(sop->event_writeset_in);
	if (sop->event_readset_out)
		free(sop->event_readset_out);
	if (sop->event_writeset_out)
		free(sop->event_writeset_out);
	if (sop->event_r_by_fd)
		free(sop->event_r_by_fd);
	if (sop->event_w_by_fd)
		free(sop->event_w_by_fd);

	memset(sop, 0, sizeof(struct selectop));
	free(sop);
}