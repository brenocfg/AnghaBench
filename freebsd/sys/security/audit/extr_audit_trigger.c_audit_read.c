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
struct uio {int dummy; } ;
struct trigger_info {int /*<<< orphan*/  trigger; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AUDITTRIGGER ; 
 int PCATCH ; 
 int PSOCK ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct trigger_info* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct trigger_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_trigger_mtx ; 
 int /*<<< orphan*/  free (struct trigger_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trigger_list ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
audit_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	int error = 0;
	struct trigger_info *ti = NULL;

	mtx_lock(&audit_trigger_mtx);
	while (TAILQ_EMPTY(&trigger_list)) {
		error = msleep(&trigger_list, &audit_trigger_mtx,
		    PSOCK | PCATCH, "auditd", 0);
		if (error)
			break;
	}
	if (!error) {
		ti = TAILQ_FIRST(&trigger_list);
		TAILQ_REMOVE(&trigger_list, ti, list);
	}
	mtx_unlock(&audit_trigger_mtx);
	if (!error) {
		error = uiomove(&ti->trigger, sizeof(ti->trigger), uio);
		free(ti, M_AUDITTRIGGER);
	}
	return (error);
}