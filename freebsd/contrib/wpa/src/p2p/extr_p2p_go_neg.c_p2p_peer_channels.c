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
struct p2p_device {int dummy; } ;
struct p2p_data {int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int p2p_peer_channels_check (struct p2p_data*,int /*<<< orphan*/ *,struct p2p_device*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int p2p_peer_channels(struct p2p_data *p2p, struct p2p_device *dev,
			     const u8 *channel_list, size_t channel_list_len)
{
	return p2p_peer_channels_check(p2p, &p2p->channels, dev,
				       channel_list, channel_list_len);
}