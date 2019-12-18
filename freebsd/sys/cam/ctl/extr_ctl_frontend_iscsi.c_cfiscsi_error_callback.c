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
struct icl_conn {int dummy; } ;
struct cfiscsi_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_WARN (struct cfiscsi_session*,char*) ; 
 struct cfiscsi_session* CONN_SESSION (struct icl_conn*) ; 
 int /*<<< orphan*/  cfiscsi_session_terminate (struct cfiscsi_session*) ; 

__attribute__((used)) static void
cfiscsi_error_callback(struct icl_conn *ic)
{
	struct cfiscsi_session *cs;

	cs = CONN_SESSION(ic);

	CFISCSI_SESSION_WARN(cs, "connection error; dropping connection");
	cfiscsi_session_terminate(cs);
}