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
struct unrhdr {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_unrhdrl (struct unrhdr*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 

void
clean_unrhdr(struct unrhdr *uh)
{

	mtx_lock(uh->mtx);
	clean_unrhdrl(uh);
	mtx_unlock(uh->mtx);
}