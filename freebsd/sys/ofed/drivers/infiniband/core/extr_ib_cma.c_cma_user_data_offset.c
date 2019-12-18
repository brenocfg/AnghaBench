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
struct TYPE_2__ {scalar_t__ ps; } ;
struct rdma_id_private {TYPE_1__ id; } ;
struct cma_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 scalar_t__ RDMA_PS_SDP ; 
 scalar_t__ cma_family (struct rdma_id_private*) ; 

__attribute__((used)) static inline int cma_user_data_offset(struct rdma_id_private *id_priv)
{
	if (cma_family(id_priv) == AF_IB)
		return 0;
	if (id_priv->id.ps == RDMA_PS_SDP)
		return 0;
	return sizeof(struct cma_hdr);
}