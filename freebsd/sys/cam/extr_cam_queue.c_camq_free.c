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
struct camq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMQ ; 
 int /*<<< orphan*/  camq_fini (struct camq*) ; 
 int /*<<< orphan*/  free (struct camq*,int /*<<< orphan*/ ) ; 

void
camq_free(struct camq *queue)
{
	if (queue != NULL) {
		camq_fini(queue);
		free(queue, M_CAMQ);
	}
}