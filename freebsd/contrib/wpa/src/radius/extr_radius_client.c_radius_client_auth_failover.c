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
struct radius_msg_list {scalar_t__ msg_type; struct radius_msg_list* next; } ;
struct radius_client_data {int /*<<< orphan*/  auth_serv_sock6; int /*<<< orphan*/  auth_serv_sock; struct radius_msg_list* msgs; int /*<<< orphan*/  ctx; struct hostapd_radius_servers* conf; } ;
struct hostapd_radius_servers {int num_auth_servers; struct hostapd_radius_server* auth_server; struct hostapd_radius_server* auth_servers; } ;
struct hostapd_radius_server {int /*<<< orphan*/  timeouts; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_NOTICE ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 scalar_t__ RADIUS_AUTH ; 
 int /*<<< orphan*/  hostapd_ip_txt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_change_server (struct radius_client_data*,struct hostapd_radius_server*,struct hostapd_radius_server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void radius_client_auth_failover(struct radius_client_data *radius)
{
	struct hostapd_radius_servers *conf = radius->conf;
	struct hostapd_radius_server *next, *old;
	struct radius_msg_list *entry;
	char abuf[50];

	old = conf->auth_server;
	hostapd_logger(radius->ctx, NULL, HOSTAPD_MODULE_RADIUS,
		       HOSTAPD_LEVEL_NOTICE,
		       "No response from Authentication server %s:%d - failover",
		       hostapd_ip_txt(&old->addr, abuf, sizeof(abuf)),
		       old->port);

	for (entry = radius->msgs; entry; entry = entry->next) {
		if (entry->msg_type == RADIUS_AUTH)
			old->timeouts++;
	}

	next = old + 1;
	if (next > &(conf->auth_servers[conf->num_auth_servers - 1]))
		next = conf->auth_servers;
	conf->auth_server = next;
	radius_change_server(radius, next, old,
			     radius->auth_serv_sock,
			     radius->auth_serv_sock6, 1);
}