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
struct sta_info {int /*<<< orphan*/  addr; } ;
struct radius_msg {int dummy; } ;
struct radius_attr_hdr {int dummy; } ;
struct hostapd_radius_attr {int /*<<< orphan*/  val; int /*<<< orphan*/  type; } ;
struct hostapd_data {int /*<<< orphan*/  rad_attr_db; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  addrtxt ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACSTR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  hostapd_config_free_radius_attr (struct hostapd_radius_attr*) ; 
 struct hostapd_radius_attr* hostapd_parse_radius_attr (char const*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int os_strlen (char*) ; 
 struct radius_attr_hdr* radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_len (int /*<<< orphan*/ ) ; 

int add_sqlite_radius_attr(struct hostapd_data *hapd, struct sta_info *sta,
			   struct radius_msg *msg, int acct)
{
#ifdef CONFIG_SQLITE
	const char *attrtxt;
	char addrtxt[3 * ETH_ALEN];
	char *sql;
	sqlite3_stmt *stmt = NULL;

	if (!hapd->rad_attr_db)
		return 0;

	os_snprintf(addrtxt, sizeof(addrtxt), MACSTR, MAC2STR(sta->addr));

	sql = "SELECT attr FROM radius_attributes WHERE sta=? AND (reqtype=? OR reqtype IS NULL);";
	if (sqlite3_prepare_v2(hapd->rad_attr_db, sql, os_strlen(sql), &stmt,
			       NULL) != SQLITE_OK) {
		wpa_printf(MSG_ERROR, "DB: Failed to prepare SQL statement: %s",
			   sqlite3_errmsg(hapd->rad_attr_db));
		return -1;
	}
	sqlite3_bind_text(stmt, 1, addrtxt, os_strlen(addrtxt), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, acct ? "acct" : "auth", 4, SQLITE_STATIC);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		struct hostapd_radius_attr *attr;
		struct radius_attr_hdr *hdr;

		attrtxt = (const char *) sqlite3_column_text(stmt, 0);
		attr = hostapd_parse_radius_attr(attrtxt);
		if (!attr) {
			wpa_printf(MSG_ERROR,
				   "Skipping invalid attribute from SQL: %s",
				   attrtxt);
			continue;
		}
		wpa_printf(MSG_DEBUG, "Adding RADIUS attribute from SQL: %s",
			   attrtxt);
		hdr = radius_msg_add_attr(msg, attr->type,
					  wpabuf_head(attr->val),
					  wpabuf_len(attr->val));
		hostapd_config_free_radius_attr(attr);
		if (!hdr) {
			wpa_printf(MSG_ERROR,
				   "Could not add RADIUS attribute from SQL");
			continue;
		}
	}

	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);
	sqlite3_finalize(stmt);
#endif /* CONFIG_SQLITE */

	return 0;
}