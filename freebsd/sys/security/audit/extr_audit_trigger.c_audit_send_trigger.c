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
struct trigger_info {unsigned int trigger; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  M_AUDITTRIGGER ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct trigger_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_isopen ; 
 int /*<<< orphan*/  audit_trigger_mtx ; 
 int /*<<< orphan*/  free (struct trigger_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 struct trigger_info* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trigger_list ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
audit_send_trigger(unsigned int trigger)
{
	struct trigger_info *ti;

	ti = malloc(sizeof *ti, M_AUDITTRIGGER, M_WAITOK);
	mtx_lock(&audit_trigger_mtx);
	if (!audit_isopen) {
		/* If nobody's listening, we ain't talking. */
		mtx_unlock(&audit_trigger_mtx);
		free(ti, M_AUDITTRIGGER);
		return (ENODEV);
	}
	ti->trigger = trigger;
	TAILQ_INSERT_TAIL(&trigger_list, ti, list);
	wakeup(&trigger_list);
	mtx_unlock(&audit_trigger_mtx);
	return (0);
}