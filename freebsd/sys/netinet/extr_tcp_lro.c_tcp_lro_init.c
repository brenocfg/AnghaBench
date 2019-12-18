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
struct lro_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_lro_entries ; 
 int tcp_lro_init_args (struct lro_ctrl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
tcp_lro_init(struct lro_ctrl *lc)
{
	return (tcp_lro_init_args(lc, NULL, tcp_lro_entries, 0));
}