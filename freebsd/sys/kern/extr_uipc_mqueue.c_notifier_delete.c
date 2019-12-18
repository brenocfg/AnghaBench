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
struct proc {int dummy; } ;
struct mqueue_notifier {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct mqueue_notifier*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notifier_free (struct mqueue_notifier*) ; 
 int /*<<< orphan*/  nt_link ; 

__attribute__((used)) static __inline void
notifier_delete(struct proc *p, struct mqueue_notifier *nt)
{
	LIST_REMOVE(nt, nt_link);
	notifier_free(nt);
}