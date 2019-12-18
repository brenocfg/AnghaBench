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
struct oper_class_map {scalar_t__ bw; } ;
struct oci_info {scalar_t__ freq; int sec_channel; int /*<<< orphan*/  chanwidth; int /*<<< orphan*/  op_class; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 scalar_t__ BW40MINUS ; 
 scalar_t__ BW40PLUS ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct oper_class_map* get_oper_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_chan_to_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oper_class_bw_to_int (struct oper_class_map const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int ocv_derive_all_parameters(struct oci_info *oci)
{
	const struct oper_class_map *op_class_map;

	oci->freq = ieee80211_chan_to_freq(NULL, oci->op_class, oci->channel);
	if (oci->freq < 0) {
		wpa_printf(MSG_INFO,
			   "Error interpreting OCI: unrecognized opclass/channel pair (%d/%d)",
			   oci->op_class, oci->channel);
		return -1;
	}

	op_class_map = get_oper_class(NULL, oci->op_class);
	if (!op_class_map) {
		wpa_printf(MSG_INFO,
			   "Error interpreting OCI: Unrecognized opclass (%d)",
			   oci->op_class);
		return -1;
	}

	oci->chanwidth = oper_class_bw_to_int(op_class_map);
	oci->sec_channel = 0;
	if (op_class_map->bw == BW40PLUS)
		oci->sec_channel = 1;
	else if (op_class_map->bw == BW40MINUS)
		oci->sec_channel = -1;

	return 0;
}