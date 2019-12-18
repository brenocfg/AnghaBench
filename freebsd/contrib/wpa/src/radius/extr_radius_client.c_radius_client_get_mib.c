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
struct radius_client_data {struct hostapd_radius_servers* conf; } ;
struct hostapd_radius_servers {int num_auth_servers; int num_acct_servers; struct hostapd_radius_server* acct_server; struct hostapd_radius_server* acct_servers; struct hostapd_radius_server* auth_server; struct hostapd_radius_server* auth_servers; } ;
struct hostapd_radius_server {int dummy; } ;

/* Variables and functions */
 scalar_t__ radius_client_dump_acct_server (char*,size_t,struct hostapd_radius_server*,struct radius_client_data*) ; 
 scalar_t__ radius_client_dump_auth_server (char*,size_t,struct hostapd_radius_server*,struct radius_client_data*) ; 

int radius_client_get_mib(struct radius_client_data *radius, char *buf,
			  size_t buflen)
{
	struct hostapd_radius_servers *conf;
	int i;
	struct hostapd_radius_server *serv;
	int count = 0;

	if (!radius)
		return 0;

	conf = radius->conf;

	if (conf->auth_servers) {
		for (i = 0; i < conf->num_auth_servers; i++) {
			serv = &conf->auth_servers[i];
			count += radius_client_dump_auth_server(
				buf + count, buflen - count, serv,
				serv == conf->auth_server ?
				radius : NULL);
		}
	}

	if (conf->acct_servers) {
		for (i = 0; i < conf->num_acct_servers; i++) {
			serv = &conf->acct_servers[i];
			count += radius_client_dump_acct_server(
				buf + count, buflen - count, serv,
				serv == conf->acct_server ?
				radius : NULL);
		}
	}

	return count;
}