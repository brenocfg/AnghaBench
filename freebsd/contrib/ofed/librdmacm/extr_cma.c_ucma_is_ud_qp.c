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
typedef  enum ibv_qp_type { ____Placeholder_ibv_qp_type } ibv_qp_type ;

/* Variables and functions */
 int IBV_QPT_UD ; 

__attribute__((used)) static int ucma_is_ud_qp(enum ibv_qp_type qp_type)
{
	return (qp_type == IBV_QPT_UD);
}