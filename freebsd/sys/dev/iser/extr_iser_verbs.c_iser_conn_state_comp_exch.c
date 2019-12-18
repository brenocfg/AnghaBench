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
struct iser_conn {int state; } ;
typedef  enum iser_conn_state { ____Placeholder_iser_conn_state } iser_conn_state ;

/* Variables and functions */

__attribute__((used)) static int iser_conn_state_comp_exch(struct iser_conn *iser_conn,
				     enum iser_conn_state comp,
				     enum iser_conn_state exch)
{
	int ret;

	ret = (iser_conn->state == comp);
	if (ret)
		iser_conn->state = exch;

	return ret;
}