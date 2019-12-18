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
struct tegra_bpmp_channel {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int __tegra_bpmp_channel_write (struct tegra_bpmp_channel*,unsigned int,unsigned long,void const*,size_t) ; 
 int tegra_bpmp_wait_request_channel_free (struct tegra_bpmp_channel*) ; 

__attribute__((used)) static ssize_t tegra_bpmp_channel_write(struct tegra_bpmp_channel *channel,
					unsigned int mrq, unsigned long flags,
					const void *data, size_t size)
{
	int err;

	err = tegra_bpmp_wait_request_channel_free(channel);
	if (err < 0)
		return err;

	return __tegra_bpmp_channel_write(channel, mrq, flags, data, size);
}