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
struct seq_file {int dummy; } ;
struct hvcall_mpp_x_data {scalar_t__ pool_spurr_cycles; scalar_t__ pool_purr_cycles; scalar_t__ pool_coalesced_bytes; scalar_t__ coalesced_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_XCMO ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 scalar_t__ h_get_mpp_x (struct hvcall_mpp_x_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 

__attribute__((used)) static void parse_mpp_x_data(struct seq_file *m)
{
	struct hvcall_mpp_x_data mpp_x_data;

	if (!firmware_has_feature(FW_FEATURE_XCMO))
		return;
	if (h_get_mpp_x(&mpp_x_data))
		return;

	seq_printf(m, "coalesced_bytes=%ld\n", mpp_x_data.coalesced_bytes);

	if (mpp_x_data.pool_coalesced_bytes)
		seq_printf(m, "pool_coalesced_bytes=%ld\n",
			   mpp_x_data.pool_coalesced_bytes);
	if (mpp_x_data.pool_purr_cycles)
		seq_printf(m, "coalesce_pool_purr=%ld\n", mpp_x_data.pool_purr_cycles);
	if (mpp_x_data.pool_spurr_cycles)
		seq_printf(m, "coalesce_pool_spurr=%ld\n", mpp_x_data.pool_spurr_cycles);
}