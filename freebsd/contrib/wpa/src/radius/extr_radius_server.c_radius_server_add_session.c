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
struct radius_session {TYPE_1__* server; int /*<<< orphan*/  t_c_filtering; int /*<<< orphan*/  nas_ip; int /*<<< orphan*/  username; int /*<<< orphan*/  mac_addr; } ;
struct os_time {int /*<<< orphan*/  sec; } ;
typedef  int /*<<< orphan*/  addr_txt ;
struct TYPE_2__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACSTR ; 
 int /*<<< orphan*/  RADIUS_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radius_server_add_session(struct radius_session *sess)
{
#ifdef CONFIG_SQLITE
	char *sql;
	char addr_txt[ETH_ALEN * 3];
	struct os_time now;

	if (!sess->server->db)
		return;


	os_snprintf(addr_txt, sizeof(addr_txt), MACSTR,
		    MAC2STR(sess->mac_addr));

	os_get_time(&now);
	sql = sqlite3_mprintf("INSERT OR REPLACE INTO current_sessions(mac_addr,identity,start_time,nas,hs20_t_c_filtering) VALUES (%Q,%Q,%d,%Q,%u)",
			      addr_txt, sess->username, now.sec,
			      sess->nas_ip, sess->t_c_filtering);
	if (sql) {
			if (sqlite3_exec(sess->server->db, sql, NULL, NULL,
					 NULL) != SQLITE_OK) {
				RADIUS_ERROR("Failed to add current_sessions entry into sqlite database: %s",
					     sqlite3_errmsg(sess->server->db));
			}
			sqlite3_free(sql);
	}
#endif /* CONFIG_SQLITE */
}