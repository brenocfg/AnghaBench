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
typedef  int u64 ;
struct iser_conn {int num_rx_descs; scalar_t__ login_resp_buf; void* rx_descs; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
is_iser_tx_desc(struct iser_conn *iser_conn, void *wr_id)
{
	void *start = iser_conn->rx_descs;
	u64 len = iser_conn->num_rx_descs * sizeof(*iser_conn->rx_descs);
	void *end = (void *)((uintptr_t)start + (uintptr_t)len);

	if (start) {
		if (wr_id >= start && wr_id < end)
			return false;
	} else {
		return ((uintptr_t)wr_id != (uintptr_t)iser_conn->login_resp_buf);
	}

	return true;
}