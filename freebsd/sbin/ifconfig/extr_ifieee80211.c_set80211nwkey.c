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
 int /*<<< orphan*/  IEEE80211_IOC_WEP ; 
 int /*<<< orphan*/  IEEE80211_IOC_WEPKEY ; 
 int /*<<< orphan*/  IEEE80211_IOC_WEPTXKEY ; 
 int IEEE80211_KEYBUF_SIZE ; 
 int IEEE80211_WEP_ON ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* get_string (char const*,char*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ isdigit (int) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set80211nwkey(const char *val, int d, int s, const struct afswtch *rafp)
{
	int		txkey;
	int		i, len;
	u_int8_t	data[IEEE80211_KEYBUF_SIZE];

	set80211(s, IEEE80211_IOC_WEP, IEEE80211_WEP_ON, 0, NULL);

	if (isdigit((int)val[0]) && val[1] == ':') {
		txkey = val[0]-'0'-1;
		val += 2;

		for (i = 0; i < 4; i++) {
			bzero(data, sizeof(data));
			len = sizeof(data);
			val = get_string(val, ",", data, &len);
			if (val == NULL)
				exit(1);

			set80211(s, IEEE80211_IOC_WEPKEY, i, len, data);
		}
	} else {
		bzero(data, sizeof(data));
		len = sizeof(data);
		get_string(val, NULL, data, &len);
		txkey = 0;

		set80211(s, IEEE80211_IOC_WEPKEY, 0, len, data);

		bzero(data, sizeof(data));
		for (i = 1; i < 4; i++)
			set80211(s, IEEE80211_IOC_WEPKEY, i, 0, data);
	}

	set80211(s, IEEE80211_IOC_WEPTXKEY, txkey, 0, NULL);
}