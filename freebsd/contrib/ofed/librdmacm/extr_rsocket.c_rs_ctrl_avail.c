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
struct rsocket {scalar_t__ ctrl_seqno; scalar_t__ ctrl_max_seqno; } ;

/* Variables and functions */

__attribute__((used)) static inline int rs_ctrl_avail(struct rsocket *rs)
{
	return rs->ctrl_seqno != rs->ctrl_max_seqno;
}