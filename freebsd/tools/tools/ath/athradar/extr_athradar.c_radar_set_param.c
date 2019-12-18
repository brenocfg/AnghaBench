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
struct radarhandler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS_PARAM_BLOCKRADAR ; 
 int /*<<< orphan*/  DFS_PARAM_ENABLE ; 
 int /*<<< orphan*/  DFS_PARAM_EN_EXTCH ; 
 int /*<<< orphan*/  DFS_PARAM_FIRPWR ; 
 int /*<<< orphan*/  DFS_PARAM_HEIGHT ; 
 int /*<<< orphan*/  DFS_PARAM_INBAND ; 
 int /*<<< orphan*/  DFS_PARAM_MAXLEN ; 
 int /*<<< orphan*/  DFS_PARAM_MAXRSSI_EN ; 
 int /*<<< orphan*/  DFS_PARAM_PRSSI ; 
 int /*<<< orphan*/  DFS_PARAM_RELPWR ; 
 int /*<<< orphan*/  DFS_PARAM_RELPWR_EN ; 
 int /*<<< orphan*/  DFS_PARAM_RELSTEP ; 
 int /*<<< orphan*/  DFS_PARAM_RELSTEP_EN ; 
 int /*<<< orphan*/  DFS_PARAM_RRSSI ; 
 int /*<<< orphan*/  DFS_PARAM_USEFIR128 ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  radarset (struct radarhandler*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
radar_set_param(struct radarhandler *radar, const char *param,
    const char *val)
{
	int v;

	v = atoi(val);

	if (strcmp(param, "enabled") == 0) {
		radarset(radar, DFS_PARAM_ENABLE, v);
	} else if (strcmp(param, "firpwr") == 0) {
		radarset(radar, DFS_PARAM_FIRPWR, v);
	} else if (strcmp(param, "rrssi") == 0) {
		radarset(radar, DFS_PARAM_RRSSI, v);
	} else if (strcmp(param, "height") == 0) {
		radarset(radar, DFS_PARAM_HEIGHT, v);
	} else if (strcmp(param, "prssi") == 0) {
		radarset(radar, DFS_PARAM_PRSSI, v);
	} else if (strcmp(param, "inband") == 0) {
		radarset(radar, DFS_PARAM_INBAND, v);
	} else if (strcmp(param, "relpwr") == 0) {
		radarset(radar, DFS_PARAM_RELPWR, v);
	} else if (strcmp(param, "relstep") == 0) {
		radarset(radar, DFS_PARAM_RELSTEP, v);
	} else if (strcmp(param, "maxlen") == 0) {
		radarset(radar, DFS_PARAM_MAXLEN, v);
	} else if (strcmp(param, "usefir128") == 0) {
		radarset(radar, DFS_PARAM_USEFIR128, v);
	} else if (strcmp(param, "blockradar") == 0) {
		radarset(radar, DFS_PARAM_BLOCKRADAR, v);
	} else if (strcmp(param, "enmaxrssi") == 0) {
		radarset(radar, DFS_PARAM_MAXRSSI_EN, v);
	} else if (strcmp(param, "extchannel") == 0) {
		radarset(radar, DFS_PARAM_EN_EXTCH, v);
	} else if (strcmp(param, "enrelpwr") == 0) {
		radarset(radar, DFS_PARAM_RELPWR_EN, v);
	} else if (strcmp(param, "en_relstep_check") == 0) {
		radarset(radar, DFS_PARAM_RELSTEP_EN, v);
	} else {
		return 0;
	}

	return 1;
}