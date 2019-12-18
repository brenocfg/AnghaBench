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
struct cfiscsi_target {int /*<<< orphan*/  ct_port; } ;
struct cfiscsi_session {int cs_ctl_initid; int /*<<< orphan*/  cs_initiator_id; struct cfiscsi_target* cs_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_DEBUG (struct cfiscsi_session*,char*,int) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_WARN (struct cfiscsi_session*,char*,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CTL ; 
 int ctl_add_initiator (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 char* strdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfiscsi_session_register_initiator(struct cfiscsi_session *cs)
{
	struct cfiscsi_target *ct;
	char *name;
	int i;

	KASSERT(cs->cs_ctl_initid == -1, ("already registered"));

	ct = cs->cs_target;
	name = strdup(cs->cs_initiator_id, M_CTL);
	i = ctl_add_initiator(&ct->ct_port, -1, 0, name);
	if (i < 0) {
		CFISCSI_SESSION_WARN(cs, "ctl_add_initiator failed with error %d",
		    i);
		cs->cs_ctl_initid = -1;
		return (1);
	}
	cs->cs_ctl_initid = i;
#if 0
	CFISCSI_SESSION_DEBUG(cs, "added initiator id %d", i);
#endif

	return (0);
}