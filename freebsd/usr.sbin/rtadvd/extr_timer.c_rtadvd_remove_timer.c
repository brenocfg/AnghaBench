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
struct rtadvd_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rtadvd_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rtadvd_timer*) ; 
 int /*<<< orphan*/  ra_timer ; 
 int /*<<< orphan*/  rat_next ; 

void
rtadvd_remove_timer(struct rtadvd_timer *rat)
{

	if (rat == NULL)
		return;

	TAILQ_REMOVE(&ra_timer, rat, rat_next);
	free(rat);
}