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
struct iscsi_session {int is_terminating; int /*<<< orphan*/  is_maintenance_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_session_logout (struct iscsi_session*) ; 

__attribute__((used)) static void
iscsi_session_terminate(struct iscsi_session *is)
{

	if (is->is_terminating)
		return;

	is->is_terminating = true;

#if 0
	iscsi_session_logout(is);
#endif
	cv_signal(&is->is_maintenance_cv);
}