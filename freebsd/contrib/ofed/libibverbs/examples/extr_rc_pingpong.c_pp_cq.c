#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct ibv_cq* cq; int /*<<< orphan*/  cq_ex; } ;
struct pingpong_context {TYPE_1__ cq_s; } ;
struct ibv_cq {int dummy; } ;

/* Variables and functions */
 struct ibv_cq* ibv_cq_ex_to_cq (int /*<<< orphan*/ ) ; 
 scalar_t__ use_ts ; 

__attribute__((used)) static struct ibv_cq *pp_cq(struct pingpong_context *ctx)
{
	return use_ts ? ibv_cq_ex_to_cq(ctx->cq_s.cq_ex) :
		ctx->cq_s.cq;
}