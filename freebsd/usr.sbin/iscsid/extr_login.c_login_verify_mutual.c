#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pdu {struct connection* pdu_connection; } ;
struct keys {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  isc_mutual_secret; int /*<<< orphan*/  isc_mutual_user; } ;
struct connection {int /*<<< orphan*/ * conn_mutual_chap; TYPE_1__ conn_conf; } ;

/* Variables and functions */
 int chap_authenticate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chap_delete (int /*<<< orphan*/ *) ; 
 int chap_receive (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fail (struct connection*,char*) ; 
 int /*<<< orphan*/  keys_delete (struct keys*) ; 
 char* keys_find (struct keys*,char*) ; 
 int /*<<< orphan*/  keys_load (struct keys*,struct pdu const*) ; 
 struct keys* keys_new () ; 
 int /*<<< orphan*/  log_debugx (char*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
login_verify_mutual(const struct pdu *response)
{
	struct connection *conn;
	struct keys *response_keys;
	const char *chap_n, *chap_r;
	int error;

	conn = response->pdu_connection;

	response_keys = keys_new();
	keys_load(response_keys, response);

        chap_n = keys_find(response_keys, "CHAP_N");
        if (chap_n == NULL)
                log_errx(1, "received CHAP Response PDU without CHAP_N");
        chap_r = keys_find(response_keys, "CHAP_R");
        if (chap_r == NULL)
                log_errx(1, "received CHAP Response PDU without CHAP_R");

	error = chap_receive(conn->conn_mutual_chap, chap_r);
	if (error != 0)
                log_errx(1, "received CHAP Response PDU with invalid CHAP_R");

	if (strcmp(chap_n, conn->conn_conf.isc_mutual_user) != 0) {
		fail(conn, "Mutual CHAP failed");
		log_errx(1, "mutual CHAP authentication failed: wrong user");
	}

	error = chap_authenticate(conn->conn_mutual_chap,
	    conn->conn_conf.isc_mutual_secret);
	if (error != 0) {
		fail(conn, "Mutual CHAP failed");
                log_errx(1, "mutual CHAP authentication failed: wrong secret");
	}

	keys_delete(response_keys);
	chap_delete(conn->conn_mutual_chap);
	conn->conn_mutual_chap = NULL;

	log_debugx("mutual CHAP authentication succeeded");
}