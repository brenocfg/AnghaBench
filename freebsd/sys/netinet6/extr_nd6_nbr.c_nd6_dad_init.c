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
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_dad_rwlock ; 
 int /*<<< orphan*/  V_dadq ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 

void
nd6_dad_init(void)
{

	rw_init(&V_dad_rwlock, "nd6 DAD queue");
	TAILQ_INIT(&V_dadq);
}