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
typedef  int /*<<< orphan*/  val ;
struct proto_conn {int dummy; } ;
struct adist_host {scalar_t__ adh_role; char* adh_localaddr; int /*<<< orphan*/  adh_conn; int /*<<< orphan*/  adh_remoteaddr; int /*<<< orphan*/  adh_fingerprint; int /*<<< orphan*/  adh_name; } ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ ADIST_ROLE_SENDER ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*,char*,...) ; 
 scalar_t__ proto_connect (char*,int /*<<< orphan*/ ,int,struct proto_conn**) ; 
 scalar_t__ proto_connection_send (int /*<<< orphan*/ ,struct proto_conn*) ; 
 scalar_t__ proto_recv (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ proto_send (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int proto_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  role2str (scalar_t__) ; 

__attribute__((used)) static void
connection_migrate(struct adist_host *adhost)
{
	struct proto_conn *conn;
	int16_t val = 0;

	pjdlog_prefix_set("[%s] (%s) ", adhost->adh_name,
	    role2str(adhost->adh_role));

	PJDLOG_ASSERT(adhost->adh_role == ADIST_ROLE_SENDER);

	if (proto_recv(adhost->adh_conn, &val, sizeof(val)) < 0) {
		pjdlog_errno(LOG_WARNING,
		    "Unable to receive connection command");
		return;
	}
	if (proto_set("tls:fingerprint", adhost->adh_fingerprint) == -1) {
		val = errno;
		pjdlog_errno(LOG_WARNING, "Unable to set fingerprint");
		goto out;
	}
	if (proto_connect(adhost->adh_localaddr[0] != '\0' ?
	    adhost->adh_localaddr : NULL,
	    adhost->adh_remoteaddr, -1, &conn) < 0) {
		val = errno;
		pjdlog_errno(LOG_WARNING, "Unable to connect to %s",
		    adhost->adh_remoteaddr);
		goto out;
	}
	val = 0;
out:
	if (proto_send(adhost->adh_conn, &val, sizeof(val)) < 0) {
		pjdlog_errno(LOG_WARNING,
		    "Unable to send reply to connection request");
	}
	if (val == 0 && proto_connection_send(adhost->adh_conn, conn) < 0)
		pjdlog_errno(LOG_WARNING, "Unable to send connection");

	pjdlog_prefix_set("%s", "");
}