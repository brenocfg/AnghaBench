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
struct cfiscsi_session {int cs_terminating; int /*<<< orphan*/  cs_login_cv; int /*<<< orphan*/  cs_maintenance_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfiscsi_session_terminate(struct cfiscsi_session *cs)
{

	cs->cs_terminating = true;
	cv_signal(&cs->cs_maintenance_cv);
#ifdef ICL_KERNEL_PROXY
	cv_signal(&cs->cs_login_cv);
#endif
}