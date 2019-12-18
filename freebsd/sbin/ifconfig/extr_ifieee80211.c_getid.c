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
struct ieee80211req {int i_val; size_t i_len; void* i_data; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_name; } ;
typedef  int /*<<< orphan*/  ireq ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_MESH_ID ; 
 int /*<<< orphan*/  IEEE80211_IOC_SSID ; 
 int /*<<< orphan*/  SIOCG80211 ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/  memset (struct ieee80211req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
getid(int s, int ix, void *data, size_t len, int *plen, int mesh)
{
	struct ieee80211req ireq;

	(void) memset(&ireq, 0, sizeof(ireq));
	(void) strlcpy(ireq.i_name, name, sizeof(ireq.i_name));
	ireq.i_type = (!mesh) ? IEEE80211_IOC_SSID : IEEE80211_IOC_MESH_ID;
	ireq.i_val = ix;
	ireq.i_data = data;
	ireq.i_len = len;
	if (ioctl(s, SIOCG80211, &ireq) < 0)
		return -1;
	*plen = ireq.i_len;
	return 0;
}