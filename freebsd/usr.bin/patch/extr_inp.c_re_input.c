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

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i_ptr ; 
 scalar_t__ i_size ; 
 int /*<<< orphan*/ * i_womp ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ ** tibuf ; 
 int tifd ; 
 int* tiline ; 
 scalar_t__ tireclen ; 
 int using_plan_a ; 

void
re_input(void)
{
	if (using_plan_a) {
		free(i_ptr);
		i_ptr = NULL;
		if (i_womp != NULL) {
			munmap(i_womp, i_size);
			i_womp = NULL;
		}
		i_size = 0;
	} else {
		using_plan_a = true;	/* maybe the next one is smaller */
		close(tifd);
		tifd = -1;
		free(tibuf[0]);
		free(tibuf[1]);
		tibuf[0] = tibuf[1] = NULL;
		tiline[0] = tiline[1] = -1;
		tireclen = 0;
	}
}