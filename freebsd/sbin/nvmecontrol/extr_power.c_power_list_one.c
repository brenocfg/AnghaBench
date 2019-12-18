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
typedef  int uint8_t ;
struct nvme_power_state {int mps_nops; int apw_aps; int mp; int idlp; int ips; int actp; int enlat; int exlat; int rrt; int rrl; int rwt; int rwl; } ;

/* Variables and functions */
 int NVME_PWR_ST_APS_MASK ; 
 int NVME_PWR_ST_APS_SHIFT ; 
 int NVME_PWR_ST_APW_MASK ; 
 int NVME_PWR_ST_APW_SHIFT ; 
 int NVME_PWR_ST_MPS_MASK ; 
 int NVME_PWR_ST_MPS_SHIFT ; 
 int NVME_PWR_ST_NOPS_MASK ; 
 int NVME_PWR_ST_NOPS_SHIFT ; 
 int /*<<< orphan*/  printf (char*,int,int,int,char,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void
power_list_one(int i, struct nvme_power_state *nps)
{
	int mpower, apower, ipower;
	uint8_t mps, nops, aps, apw;

	mps = (nps->mps_nops >> NVME_PWR_ST_MPS_SHIFT) &
		NVME_PWR_ST_MPS_MASK;
	nops = (nps->mps_nops >> NVME_PWR_ST_NOPS_SHIFT) &
		NVME_PWR_ST_NOPS_MASK;
	apw = (nps->apw_aps >> NVME_PWR_ST_APW_SHIFT) &
		NVME_PWR_ST_APW_MASK;
	aps = (nps->apw_aps >> NVME_PWR_ST_APS_SHIFT) &
		NVME_PWR_ST_APS_MASK;

	mpower = nps->mp;
	if (mps == 0)
		mpower *= 100;
	ipower = nps->idlp;
	if (nps->ips == 1)
		ipower *= 100;
	apower = nps->actp;
	if (aps == 1)
		apower *= 100;
	printf("%2d: %2d.%04dW%c %3d.%03dms %3d.%03dms %2d %2d %2d %2d %2d.%04dW %2d.%04dW %d\n",
	       i, mpower / 10000, mpower % 10000,
	       nops ? '*' : ' ', nps->enlat / 1000, nps->enlat % 1000,
	       nps->exlat / 1000, nps->exlat % 1000, nps->rrt, nps->rrl,
	       nps->rwt, nps->rwl, ipower / 10000, ipower % 10000,
	       apower / 10000, apower % 10000, apw);
}