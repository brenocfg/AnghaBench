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
struct mqueue_notifier {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mqnoti_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mqueue_notifier*) ; 

__attribute__((used)) static __inline void
notifier_free(struct mqueue_notifier *p)
{
	uma_zfree(mqnoti_zone, p);
}