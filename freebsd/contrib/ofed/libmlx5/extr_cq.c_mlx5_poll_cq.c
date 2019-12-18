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
struct ibv_wc {int dummy; } ;
struct ibv_cq {int dummy; } ;

/* Variables and functions */
 int poll_cq (struct ibv_cq*,int,struct ibv_wc*,int /*<<< orphan*/ ) ; 

int mlx5_poll_cq(struct ibv_cq *ibcq, int ne, struct ibv_wc *wc)
{
	return poll_cq(ibcq, ne, wc, 0);
}