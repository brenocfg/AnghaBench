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
struct ibv_srq {int dummy; } ;
struct ibv_recv_wr {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

int c4iw_post_srq_recv(struct ibv_srq *ibsrq, struct ibv_recv_wr *wr,
		       struct ibv_recv_wr **bad_wr)
{
	return ENOSYS;
}