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
struct pollop {struct pollop* idxplus1_by_fd; struct pollop* event_w_back; struct pollop* event_r_back; struct pollop* event_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pollop*) ; 
 int /*<<< orphan*/  memset (struct pollop*,int /*<<< orphan*/ ,int) ; 

void
poll_dealloc(void *arg)
{
	struct pollop *pop = arg;

	if (pop->event_set)
		free(pop->event_set);
	if (pop->event_r_back)
		free(pop->event_r_back);
	if (pop->event_w_back)
		free(pop->event_w_back);
	if (pop->idxplus1_by_fd)
		free(pop->idxplus1_by_fd);

	memset(pop, 0, sizeof(struct pollop));
	free(pop);
}