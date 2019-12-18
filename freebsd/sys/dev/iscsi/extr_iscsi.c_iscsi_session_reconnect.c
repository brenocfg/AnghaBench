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
struct iscsi_session {int is_reconnecting; int /*<<< orphan*/  is_maintenance_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iscsi_session_reconnect(struct iscsi_session *is)
{

	/*
	 * XXX: We can't use locking here, because
	 * 	it's being called from various contexts.
	 * 	Hope it doesn't break anything.
	 */
	if (is->is_reconnecting)
		return;

	is->is_reconnecting = true;
	cv_signal(&is->is_maintenance_cv);
}