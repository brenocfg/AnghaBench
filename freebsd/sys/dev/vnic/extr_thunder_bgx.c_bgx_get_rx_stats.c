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
typedef  int /*<<< orphan*/  uint64_t ;
struct bgx {int dummy; } ;

/* Variables and functions */
 scalar_t__ BGX_CMRX_RX_STAT0 ; 
 int MAX_BGX_PER_CN88XX ; 
 int /*<<< orphan*/  bgx_reg_read (struct bgx*,int,scalar_t__) ; 
 struct bgx** bgx_vnic ; 

uint64_t
bgx_get_rx_stats(int node, int bgx_idx, int lmac, int idx)
{
	struct bgx *bgx;

	bgx = bgx_vnic[(node * MAX_BGX_PER_CN88XX) + bgx_idx];
	if (bgx == NULL)
		return (0);

	if (idx > 8)
		lmac = (0);
	return (bgx_reg_read(bgx, lmac, BGX_CMRX_RX_STAT0 + (idx * 8)));
}