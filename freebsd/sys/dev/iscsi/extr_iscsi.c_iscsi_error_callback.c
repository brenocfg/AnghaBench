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
struct iscsi_session {int dummy; } ;
struct icl_conn {int dummy; } ;

/* Variables and functions */
 struct iscsi_session* CONN_SESSION (struct icl_conn*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*) ; 
 int /*<<< orphan*/  iscsi_session_reconnect (struct iscsi_session*) ; 

__attribute__((used)) static void
iscsi_error_callback(struct icl_conn *ic)
{
	struct iscsi_session *is;

	is = CONN_SESSION(ic);

	ISCSI_SESSION_WARN(is, "connection error; reconnecting");
	iscsi_session_reconnect(is);
}