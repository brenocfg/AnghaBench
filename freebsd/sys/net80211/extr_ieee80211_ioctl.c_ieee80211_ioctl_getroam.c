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
struct ieee80211vap {int /*<<< orphan*/  iv_roamparms; } ;
struct ieee80211req {size_t i_len; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
ieee80211_ioctl_getroam(struct ieee80211vap *vap,
	const struct ieee80211req *ireq)
{
	size_t len = ireq->i_len;
	/* NB: accept short requests for backwards compat */
	if (len > sizeof(vap->iv_roamparms))
		len = sizeof(vap->iv_roamparms);
	return copyout(vap->iv_roamparms, ireq->i_data, len);
}