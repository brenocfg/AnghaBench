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
typedef  int /*<<< orphan*/  u_int8_t ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_SSID ; 
 int IEEE80211_NWID_LEN ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * get_string (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
set80211ssid(const char *val, int d, int s, const struct afswtch *rafp)
{
	int		ssid;
	int		len;
	u_int8_t	data[IEEE80211_NWID_LEN];

	ssid = 0;
	len = strlen(val);
	if (len > 2 && isdigit((int)val[0]) && val[1] == ':') {
		ssid = atoi(val)-1;
		val += 2;
	}

	bzero(data, sizeof(data));
	len = sizeof(data);
	if (get_string(val, NULL, data, &len) == NULL)
		exit(1);

	set80211(s, IEEE80211_IOC_SSID, ssid, len, data);
}