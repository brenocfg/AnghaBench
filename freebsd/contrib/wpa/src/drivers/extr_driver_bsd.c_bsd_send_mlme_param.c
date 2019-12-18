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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211req_mlme {int /*<<< orphan*/  im_macaddr; int /*<<< orphan*/  im_reason; int /*<<< orphan*/  im_op; } ;
typedef  int /*<<< orphan*/  mlme ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_IOC_MLME ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211req_mlme*,int /*<<< orphan*/ ,int) ; 
 int set80211var (void*,int /*<<< orphan*/ ,struct ieee80211req_mlme*,int) ; 

__attribute__((used)) static int
bsd_send_mlme_param(void *priv, const u8 op, const u16 reason, const u8 *addr)
{
	struct ieee80211req_mlme mlme;

	os_memset(&mlme, 0, sizeof(mlme));
	mlme.im_op = op;
	mlme.im_reason = reason;
	os_memcpy(mlme.im_macaddr, addr, IEEE80211_ADDR_LEN);
	return set80211var(priv, IEEE80211_IOC_MLME, &mlme, sizeof(mlme));
}