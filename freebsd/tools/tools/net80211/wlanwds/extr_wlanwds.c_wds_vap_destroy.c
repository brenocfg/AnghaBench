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
struct ieee80211req {int /*<<< orphan*/  i_name; } ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCIFDESTROY ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/  memset (struct ieee80211req*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
wds_vap_destroy(const char *ifname)
{
	struct ieee80211req ifr;
	int s, status;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		syslog(LOG_ERR, "socket(SOCK_DRAGM): %m");
		return -1;
	}
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.i_name, ifname, IFNAMSIZ);
	if (ioctl(s, SIOCIFDESTROY, &ifr) < 0) {
		syslog(LOG_ERR, "ioctl(SIOCIFDESTROY): %m");
		status = -1;
	} else
		status = 0;
	close(s);
	return status;
}