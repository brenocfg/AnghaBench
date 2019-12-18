#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  imr_dest; } ;
struct wlan_mesh_route {int /*<<< orphan*/  mroute_status; TYPE_1__ imroute; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  RowStatus_notReady ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wlan_mesh_route*,int /*<<< orphan*/ ,int) ; 

struct wlan_mesh_route *
wlan_mesh_new_route(const uint8_t *dstmac)
{
	struct wlan_mesh_route *wmr;

	if ((wmr = (struct wlan_mesh_route *)malloc(sizeof(*wmr))) == NULL)
		return (NULL);

	memset(wmr, 0, sizeof(*wmr));
	memcpy(wmr->imroute.imr_dest, dstmac, IEEE80211_ADDR_LEN);
	wmr->mroute_status = RowStatus_notReady;

	return (wmr);
}