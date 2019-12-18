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
typedef  int /*<<< orphan*/  uint8_t ;
struct ibv_wc {int dummy; } ;
struct ibv_pd {int /*<<< orphan*/  context; } ;
struct ibv_grh {int dummy; } ;
struct ibv_ah_attr {int dummy; } ;
struct ibv_ah {int dummy; } ;

/* Variables and functions */
 struct ibv_ah* ibv_create_ah (struct ibv_pd*,struct ibv_ah_attr*) ; 
 int ibv_init_ah_from_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibv_wc*,struct ibv_grh*,struct ibv_ah_attr*) ; 

struct ibv_ah *ibv_create_ah_from_wc(struct ibv_pd *pd, struct ibv_wc *wc,
				     struct ibv_grh *grh, uint8_t port_num)
{
	struct ibv_ah_attr ah_attr;
	int ret;

	ret = ibv_init_ah_from_wc(pd->context, port_num, wc, grh, &ah_attr);
	if (ret)
		return NULL;

	return ibv_create_ah(pd, &ah_attr);
}