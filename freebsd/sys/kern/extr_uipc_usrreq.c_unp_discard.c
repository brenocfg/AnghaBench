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
struct unp_defer {struct file* ud_fp; } ;
struct thread {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct unp_defer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNP_DEFERRED_LOCK () ; 
 int /*<<< orphan*/  UNP_DEFERRED_UNLOCK () ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  closef (struct file*,struct thread*) ; 
 struct unp_defer* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  ud_link ; 
 int /*<<< orphan*/  unp_defer_task ; 
 int /*<<< orphan*/  unp_defers ; 
 int /*<<< orphan*/  unp_defers_count ; 
 scalar_t__ unp_externalize_fp (struct file*) ; 

__attribute__((used)) static void
unp_discard(struct file *fp)
{
	struct unp_defer *dr;

	if (unp_externalize_fp(fp)) {
		dr = malloc(sizeof(*dr), M_TEMP, M_WAITOK);
		dr->ud_fp = fp;
		UNP_DEFERRED_LOCK();
		SLIST_INSERT_HEAD(&unp_defers, dr, ud_link);
		UNP_DEFERRED_UNLOCK();
		atomic_add_int(&unp_defers_count, 1);
		taskqueue_enqueue(taskqueue_thread, &unp_defer_task);
	} else
		(void) closef(fp, (struct thread *)NULL);
}