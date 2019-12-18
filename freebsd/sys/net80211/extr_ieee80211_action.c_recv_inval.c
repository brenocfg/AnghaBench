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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
recv_inval(struct ieee80211_node *ni, const struct ieee80211_frame *wh,
	const uint8_t *frm, const uint8_t *efrm)
{
	return EINVAL;
}