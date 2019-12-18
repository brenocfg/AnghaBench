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
 int /*<<< orphan*/  IEEE80211_IOC_MESH_ID ; 
 int IEEE80211_NWID_LEN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * get_string (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set80211 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set80211meshid(const char *val, int d, int s, const struct afswtch *rafp)
{
	int		len;
	u_int8_t	data[IEEE80211_NWID_LEN];

	memset(data, 0, sizeof(data));
	len = sizeof(data);
	if (get_string(val, NULL, data, &len) == NULL)
		exit(1);

	set80211(s, IEEE80211_IOC_MESH_ID, 0, len, data);
}