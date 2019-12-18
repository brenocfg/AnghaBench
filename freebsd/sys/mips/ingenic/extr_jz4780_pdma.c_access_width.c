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
typedef  int uint32_t ;
struct xdma_request {int src_width; int dst_width; } ;

/* Variables and functions */
 int DCM_DP_1 ; 
 int DCM_DP_2 ; 
 int DCM_DP_4 ; 
 int DCM_SP_1 ; 
 int DCM_SP_2 ; 
 int DCM_SP_4 ; 
 int DCM_TSZ_1 ; 
 int DCM_TSZ_2 ; 
 int DCM_TSZ_4 ; 
 int max (int,int) ; 

__attribute__((used)) static int
access_width(struct xdma_request *req, uint32_t *dcm, uint32_t *max_width)
{

	*dcm = 0;
	*max_width = max(req->src_width, req->dst_width);

	switch (req->src_width) {
	case 1:
		*dcm |= DCM_SP_1;
		break;
	case 2:
		*dcm |= DCM_SP_2;
		break;
	case 4:
		*dcm |= DCM_SP_4;
		break;
	default:
		return (-1);
	}

	switch (req->dst_width) {
	case 1:
		*dcm |= DCM_DP_1;
		break;
	case 2:
		*dcm |= DCM_DP_2;
		break;
	case 4:
		*dcm |= DCM_DP_4;
		break;
	default:
		return (-1);
	}

	switch (*max_width) {
	case 1:
		*dcm |= DCM_TSZ_1;
		break;
	case 2:
		*dcm |= DCM_TSZ_2;
		break;
	case 4:
		*dcm |= DCM_TSZ_4;
		break;
	default:
		return (-1);
	};

	return (0);
}