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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  nas; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct radius_server_data {int /*<<< orphan*/  auth_sock; int /*<<< orphan*/  db; } ;
struct radius_msg {int dummy; } ;
struct radius_client {int pending_dac_disconnect_id; int pending_dac_coa_id; int /*<<< orphan*/  pending_dac_coa_addr; struct radius_msg* pending_dac_coa_req; int /*<<< orphan*/  pending_dac_disconnect_addr; struct radius_msg* pending_dac_disconnect_req; int /*<<< orphan*/  shared_secret_len; scalar_t__ shared_secret; int /*<<< orphan*/  next_dac_identifier; } ;
struct os_time {int /*<<< orphan*/  sec; } ;
struct db_session_fields {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  nas; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  fields ;
typedef  int /*<<< orphan*/  das ;
typedef  int /*<<< orphan*/  addrtxt ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MAC2STR (int*) ; 
 int /*<<< orphan*/  MACSTR ; 
 scalar_t__ MSG_MSGDUMP ; 
 int /*<<< orphan*/  RADIUS_802_1X_ADDR_FORMAT ; 
 int /*<<< orphan*/  RADIUS_ATTR_CALLING_STATION_ID ; 
 int /*<<< orphan*/  RADIUS_ATTR_EVENT_TIMESTAMP ; 
 int /*<<< orphan*/  RADIUS_CODE_COA_REQUEST ; 
 int /*<<< orphan*/  RADIUS_CODE_DISCONNECT_REQUEST ; 
 int /*<<< orphan*/  RADIUS_DEBUG (char*) ; 
 int /*<<< orphan*/  RADIUS_ERROR (char*,...) ; 
 int /*<<< orphan*/  RADIUS_VENDOR_ATTR_WFA_HS20_T_C_FILTERING ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free_db_session_fields (struct sockaddr_in*) ; 
 int /*<<< orphan*/  get_db_session_fields ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ hwaddr_aton (char const*,int*) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_get_time (struct os_time*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* os_strchr (char const*,char) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 scalar_t__ os_strstr (char const*,char*) ; 
 int /*<<< orphan*/  radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_add_wfa (struct radius_msg*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  radius_msg_dump (struct radius_msg*) ; 
 int /*<<< orphan*/  radius_msg_finish_acct (struct radius_msg*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 struct wpabuf* radius_msg_get_buf (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int) ; 
 struct radius_client* radius_server_get_client (struct radius_server_data*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct sockaddr_in*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_debug_level ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

int radius_server_dac_request(struct radius_server_data *data, const char *req)
{
#ifdef CONFIG_SQLITE
	char *sql;
	int res;
	int disconnect;
	const char *pos = req;
	u8 addr[ETH_ALEN];
	char addrtxt[3 * ETH_ALEN];
	int t_c_clear = 0;
	struct db_session_fields fields;
	struct sockaddr_in das;
	struct radius_client *client;
	struct radius_msg *msg;
	struct wpabuf *buf;
	u8 identifier;
	struct os_time now;

	if (!data)
		return -1;

	/* req: <disconnect|coa> <MAC Address> [t_c_clear] */

	if (os_strncmp(pos, "disconnect ", 11) == 0) {
		disconnect = 1;
		pos += 11;
	} else if (os_strncmp(req, "coa ", 4) == 0) {
		disconnect = 0;
		pos += 4;
	} else {
		return -1;
	}

	if (hwaddr_aton(pos, addr))
		return -1;
	pos = os_strchr(pos, ' ');
	if (pos) {
		if (os_strstr(pos, "t_c_clear"))
			t_c_clear = 1;
	}

	if (!disconnect && !t_c_clear) {
		RADIUS_ERROR("DAC request for CoA without any authorization change");
		return -1;
	}

	if (!data->db) {
		RADIUS_ERROR("SQLite database not in use");
		return -1;
	}

	os_snprintf(addrtxt, sizeof(addrtxt), MACSTR, MAC2STR(addr));

	sql = sqlite3_mprintf("SELECT * FROM current_sessions WHERE mac_addr=%Q",
			      addrtxt);
	if (!sql)
		return -1;

	os_memset(&fields, 0, sizeof(fields));
	res = sqlite3_exec(data->db, sql, get_db_session_fields, &fields, NULL);
	sqlite3_free(sql);
	if (res != SQLITE_OK) {
		RADIUS_ERROR("Failed to find matching current_sessions entry from sqlite database: %s",
			     sqlite3_errmsg(data->db));
		free_db_session_fields(&fields);
		return -1;
	}

	if (!fields.nas) {
		RADIUS_ERROR("No NAS information found from current_sessions");
		free_db_session_fields(&fields);
		return -1;
	}

	os_memset(&das, 0, sizeof(das));
	das.sin_family = AF_INET;
	das.sin_addr.s_addr = inet_addr(fields.nas);
	das.sin_port = htons(3799);

	free_db_session_fields(&fields);

	client = radius_server_get_client(data, &das.sin_addr, 0);
	if (!client) {
		RADIUS_ERROR("No NAS information available to protect the packet");
		return -1;
	}

	identifier = client->next_dac_identifier++;

	msg = radius_msg_new(disconnect ? RADIUS_CODE_DISCONNECT_REQUEST :
			     RADIUS_CODE_COA_REQUEST, identifier);
	if (!msg)
		return -1;

	os_snprintf(addrtxt, sizeof(addrtxt), RADIUS_802_1X_ADDR_FORMAT,
		    MAC2STR(addr));
	if (!radius_msg_add_attr(msg, RADIUS_ATTR_CALLING_STATION_ID,
				 (u8 *) addrtxt, os_strlen(addrtxt))) {
		RADIUS_ERROR("Could not add Calling-Station-Id");
		radius_msg_free(msg);
		return -1;
	}

	if (!disconnect && t_c_clear) {
		u8 val[4] = { 0x00, 0x00, 0x00, 0x00 }; /* E=0 */

		if (!radius_msg_add_wfa(
			    msg, RADIUS_VENDOR_ATTR_WFA_HS20_T_C_FILTERING,
			    val, sizeof(val))) {
			RADIUS_DEBUG("Failed to add WFA-HS20-T-C-Filtering");
			radius_msg_free(msg);
			return -1;
		}
	}

	os_get_time(&now);
	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_EVENT_TIMESTAMP,
				       now.sec)) {
		RADIUS_ERROR("Failed to add Event-Timestamp attribute");
		radius_msg_free(msg);
		return -1;
	}

	radius_msg_finish_acct(msg, (u8 *) client->shared_secret,
			       client->shared_secret_len);

	if (wpa_debug_level <= MSG_MSGDUMP)
		radius_msg_dump(msg);

	buf = radius_msg_get_buf(msg);
	if (sendto(data->auth_sock, wpabuf_head(buf), wpabuf_len(buf), 0,
		   (struct sockaddr *) &das, sizeof(das)) < 0) {
		RADIUS_ERROR("Failed to send packet - sendto: %s",
			     strerror(errno));
		radius_msg_free(msg);
		return -1;
	}

	if (disconnect) {
		radius_msg_free(client->pending_dac_disconnect_req);
		client->pending_dac_disconnect_req = msg;
		client->pending_dac_disconnect_id = identifier;
		os_memcpy(client->pending_dac_disconnect_addr, addr, ETH_ALEN);
	} else {
		radius_msg_free(client->pending_dac_coa_req);
		client->pending_dac_coa_req = msg;
		client->pending_dac_coa_id = identifier;
		os_memcpy(client->pending_dac_coa_addr, addr, ETH_ALEN);
	}

	return 0;
#else /* CONFIG_SQLITE */
	return -1;
#endif /* CONFIG_SQLITE */
}