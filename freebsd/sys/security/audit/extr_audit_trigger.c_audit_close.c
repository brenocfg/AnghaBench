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
struct trigger_info {int dummy; } ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AUDITTRIGGER ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct trigger_info* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct trigger_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ audit_isopen ; 
 int /*<<< orphan*/  audit_trigger_mtx ; 
 int /*<<< orphan*/  free (struct trigger_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trigger_list ; 

__attribute__((used)) static int
audit_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct trigger_info *ti;

	/* Flush the queue of pending trigger events. */
	mtx_lock(&audit_trigger_mtx);
	audit_isopen = 0;
	while (!TAILQ_EMPTY(&trigger_list)) {
		ti = TAILQ_FIRST(&trigger_list);
		TAILQ_REMOVE(&trigger_list, ti, list);
		free(ti, M_AUDITTRIGGER);
	}
	mtx_unlock(&audit_trigger_mtx);

	return (0);
}