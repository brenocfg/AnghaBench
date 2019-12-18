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
typedef  int u_int ;
struct uni_abr_rec {int present; int nrm; int trm; int cdf; int adtf; } ;

/* Variables and functions */
 int UNI_ABR_REC_ADTF_P ; 
 int UNI_ABR_REC_CDF_P ; 
 int UNI_ABR_REC_NRM_P ; 
 int UNI_ABR_REC_TRM_P ; 

__attribute__((used)) static u_int
encode_abr_rec(struct uni_abr_rec *rec)
{
	u_int ret = rec->present & 0xf000;

	if(ret & UNI_ABR_REC_NRM_P)
		ret |= (rec->nrm & 0x7) << 25;
	if(ret & UNI_ABR_REC_TRM_P)
		ret |= (rec->trm & 0x7) << 22;
	if(ret & UNI_ABR_REC_CDF_P)
		ret |= (rec->cdf & 0x7) << 19;
	if(ret & UNI_ABR_REC_ADTF_P)
		ret |= (rec->adtf & 0x3ff) << 9;

	return ret;
}