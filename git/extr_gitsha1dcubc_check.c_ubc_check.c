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

/* Variables and functions */
 int const DV_II_45_0_bit ; 
 int const DV_II_46_0_bit ; 
 int const DV_II_46_2_bit ; 
 int const DV_II_47_0_bit ; 
 int const DV_II_48_0_bit ; 
 int const DV_II_49_0_bit ; 
 int const DV_II_49_2_bit ; 
 int const DV_II_50_0_bit ; 
 int const DV_II_50_2_bit ; 
 int const DV_II_51_0_bit ; 
 int const DV_II_51_2_bit ; 
 int const DV_II_52_0_bit ; 
 int const DV_II_53_0_bit ; 
 int const DV_II_54_0_bit ; 
 int const DV_II_55_0_bit ; 
 int const DV_II_56_0_bit ; 
 int const DV_I_43_0_bit ; 
 int const DV_I_44_0_bit ; 
 int const DV_I_45_0_bit ; 
 int const DV_I_46_0_bit ; 
 int const DV_I_46_2_bit ; 
 int const DV_I_47_0_bit ; 
 int const DV_I_47_2_bit ; 
 int const DV_I_48_0_bit ; 
 int const DV_I_48_2_bit ; 
 int const DV_I_49_0_bit ; 
 int const DV_I_49_2_bit ; 
 int const DV_I_50_0_bit ; 
 int const DV_I_50_2_bit ; 
 int const DV_I_51_0_bit ; 
 int const DV_I_51_2_bit ; 
 int const DV_I_52_0_bit ; 

void ubc_check(const uint32_t W[80], uint32_t dvmask[1])
{
	uint32_t mask = ~((uint32_t)(0));
	mask &= (((((W[44]^W[45])>>29)&1)-1) | ~(DV_I_48_0_bit|DV_I_51_0_bit|DV_I_52_0_bit|DV_II_45_0_bit|DV_II_46_0_bit|DV_II_50_0_bit|DV_II_51_0_bit));
	mask &= (((((W[49]^W[50])>>29)&1)-1) | ~(DV_I_46_0_bit|DV_II_45_0_bit|DV_II_50_0_bit|DV_II_51_0_bit|DV_II_55_0_bit|DV_II_56_0_bit));
	mask &= (((((W[48]^W[49])>>29)&1)-1) | ~(DV_I_45_0_bit|DV_I_52_0_bit|DV_II_49_0_bit|DV_II_50_0_bit|DV_II_54_0_bit|DV_II_55_0_bit));
	mask &= ((((W[47]^(W[50]>>25))&(1<<4))-(1<<4)) | ~(DV_I_47_0_bit|DV_I_49_0_bit|DV_I_51_0_bit|DV_II_45_0_bit|DV_II_51_0_bit|DV_II_56_0_bit));
	mask &= (((((W[47]^W[48])>>29)&1)-1) | ~(DV_I_44_0_bit|DV_I_51_0_bit|DV_II_48_0_bit|DV_II_49_0_bit|DV_II_53_0_bit|DV_II_54_0_bit));
	mask &= (((((W[46]>>4)^(W[49]>>29))&1)-1) | ~(DV_I_46_0_bit|DV_I_48_0_bit|DV_I_50_0_bit|DV_I_52_0_bit|DV_II_50_0_bit|DV_II_55_0_bit));
	mask &= (((((W[46]^W[47])>>29)&1)-1) | ~(DV_I_43_0_bit|DV_I_50_0_bit|DV_II_47_0_bit|DV_II_48_0_bit|DV_II_52_0_bit|DV_II_53_0_bit));
	mask &= (((((W[45]>>4)^(W[48]>>29))&1)-1) | ~(DV_I_45_0_bit|DV_I_47_0_bit|DV_I_49_0_bit|DV_I_51_0_bit|DV_II_49_0_bit|DV_II_54_0_bit));
	mask &= (((((W[45]^W[46])>>29)&1)-1) | ~(DV_I_49_0_bit|DV_I_52_0_bit|DV_II_46_0_bit|DV_II_47_0_bit|DV_II_51_0_bit|DV_II_52_0_bit));
	mask &= (((((W[44]>>4)^(W[47]>>29))&1)-1) | ~(DV_I_44_0_bit|DV_I_46_0_bit|DV_I_48_0_bit|DV_I_50_0_bit|DV_II_48_0_bit|DV_II_53_0_bit));
	mask &= (((((W[43]>>4)^(W[46]>>29))&1)-1) | ~(DV_I_43_0_bit|DV_I_45_0_bit|DV_I_47_0_bit|DV_I_49_0_bit|DV_II_47_0_bit|DV_II_52_0_bit));
	mask &= (((((W[43]^W[44])>>29)&1)-1) | ~(DV_I_47_0_bit|DV_I_50_0_bit|DV_I_51_0_bit|DV_II_45_0_bit|DV_II_49_0_bit|DV_II_50_0_bit));
	mask &= (((((W[42]>>4)^(W[45]>>29))&1)-1) | ~(DV_I_44_0_bit|DV_I_46_0_bit|DV_I_48_0_bit|DV_I_52_0_bit|DV_II_46_0_bit|DV_II_51_0_bit));
	mask &= (((((W[41]>>4)^(W[44]>>29))&1)-1) | ~(DV_I_43_0_bit|DV_I_45_0_bit|DV_I_47_0_bit|DV_I_51_0_bit|DV_II_45_0_bit|DV_II_50_0_bit));
	mask &= (((((W[40]^W[41])>>29)&1)-1) | ~(DV_I_44_0_bit|DV_I_47_0_bit|DV_I_48_0_bit|DV_II_46_0_bit|DV_II_47_0_bit|DV_II_56_0_bit));
	mask &= (((((W[54]^W[55])>>29)&1)-1) | ~(DV_I_51_0_bit|DV_II_47_0_bit|DV_II_50_0_bit|DV_II_55_0_bit|DV_II_56_0_bit));
	mask &= (((((W[53]^W[54])>>29)&1)-1) | ~(DV_I_50_0_bit|DV_II_46_0_bit|DV_II_49_0_bit|DV_II_54_0_bit|DV_II_55_0_bit));
	mask &= (((((W[52]^W[53])>>29)&1)-1) | ~(DV_I_49_0_bit|DV_II_45_0_bit|DV_II_48_0_bit|DV_II_53_0_bit|DV_II_54_0_bit));
	mask &= ((((W[50]^(W[53]>>25))&(1<<4))-(1<<4)) | ~(DV_I_50_0_bit|DV_I_52_0_bit|DV_II_46_0_bit|DV_II_48_0_bit|DV_II_54_0_bit));
	mask &= (((((W[50]^W[51])>>29)&1)-1) | ~(DV_I_47_0_bit|DV_II_46_0_bit|DV_II_51_0_bit|DV_II_52_0_bit|DV_II_56_0_bit));
	mask &= ((((W[49]^(W[52]>>25))&(1<<4))-(1<<4)) | ~(DV_I_49_0_bit|DV_I_51_0_bit|DV_II_45_0_bit|DV_II_47_0_bit|DV_II_53_0_bit));
	mask &= ((((W[48]^(W[51]>>25))&(1<<4))-(1<<4)) | ~(DV_I_48_0_bit|DV_I_50_0_bit|DV_I_52_0_bit|DV_II_46_0_bit|DV_II_52_0_bit));
	mask &= (((((W[42]^W[43])>>29)&1)-1) | ~(DV_I_46_0_bit|DV_I_49_0_bit|DV_I_50_0_bit|DV_II_48_0_bit|DV_II_49_0_bit));
	mask &= (((((W[41]^W[42])>>29)&1)-1) | ~(DV_I_45_0_bit|DV_I_48_0_bit|DV_I_49_0_bit|DV_II_47_0_bit|DV_II_48_0_bit));
	mask &= (((((W[40]>>4)^(W[43]>>29))&1)-1) | ~(DV_I_44_0_bit|DV_I_46_0_bit|DV_I_50_0_bit|DV_II_49_0_bit|DV_II_56_0_bit));
	mask &= (((((W[39]>>4)^(W[42]>>29))&1)-1) | ~(DV_I_43_0_bit|DV_I_45_0_bit|DV_I_49_0_bit|DV_II_48_0_bit|DV_II_55_0_bit));
	if (mask & (DV_I_44_0_bit|DV_I_48_0_bit|DV_II_47_0_bit|DV_II_54_0_bit|DV_II_56_0_bit))
		mask &= (((((W[38]>>4)^(W[41]>>29))&1)-1) | ~(DV_I_44_0_bit|DV_I_48_0_bit|DV_II_47_0_bit|DV_II_54_0_bit|DV_II_56_0_bit));
	mask &= (((((W[37]>>4)^(W[40]>>29))&1)-1) | ~(DV_I_43_0_bit|DV_I_47_0_bit|DV_II_46_0_bit|DV_II_53_0_bit|DV_II_55_0_bit));
	if (mask & (DV_I_52_0_bit|DV_II_48_0_bit|DV_II_51_0_bit|DV_II_56_0_bit))
		mask &= (((((W[55]^W[56])>>29)&1)-1) | ~(DV_I_52_0_bit|DV_II_48_0_bit|DV_II_51_0_bit|DV_II_56_0_bit));
	if (mask & (DV_I_52_0_bit|DV_II_48_0_bit|DV_II_50_0_bit|DV_II_56_0_bit))
		mask &= ((((W[52]^(W[55]>>25))&(1<<4))-(1<<4)) | ~(DV_I_52_0_bit|DV_II_48_0_bit|DV_II_50_0_bit|DV_II_56_0_bit));
	if (mask & (DV_I_51_0_bit|DV_II_47_0_bit|DV_II_49_0_bit|DV_II_55_0_bit))
		mask &= ((((W[51]^(W[54]>>25))&(1<<4))-(1<<4)) | ~(DV_I_51_0_bit|DV_II_47_0_bit|DV_II_49_0_bit|DV_II_55_0_bit));
	if (mask & (DV_I_48_0_bit|DV_II_47_0_bit|DV_II_52_0_bit|DV_II_53_0_bit))
		mask &= (((((W[51]^W[52])>>29)&1)-1) | ~(DV_I_48_0_bit|DV_II_47_0_bit|DV_II_52_0_bit|DV_II_53_0_bit));
	if (mask & (DV_I_46_0_bit|DV_I_49_0_bit|DV_II_45_0_bit|DV_II_48_0_bit))
		mask &= (((((W[36]>>4)^(W[40]>>29))&1)-1) | ~(DV_I_46_0_bit|DV_I_49_0_bit|DV_II_45_0_bit|DV_II_48_0_bit));
	if (mask & (DV_I_52_0_bit|DV_II_48_0_bit|DV_II_49_0_bit))
		mask &= ((0-(((W[53]^W[56])>>29)&1)) | ~(DV_I_52_0_bit|DV_II_48_0_bit|DV_II_49_0_bit));
	if (mask & (DV_I_50_0_bit|DV_II_46_0_bit|DV_II_47_0_bit))
		mask &= ((0-(((W[51]^W[54])>>29)&1)) | ~(DV_I_50_0_bit|DV_II_46_0_bit|DV_II_47_0_bit));
	if (mask & (DV_I_49_0_bit|DV_I_51_0_bit|DV_II_45_0_bit))
		mask &= ((0-(((W[50]^W[52])>>29)&1)) | ~(DV_I_49_0_bit|DV_I_51_0_bit|DV_II_45_0_bit));
	if (mask & (DV_I_48_0_bit|DV_I_50_0_bit|DV_I_52_0_bit))
		mask &= ((0-(((W[49]^W[51])>>29)&1)) | ~(DV_I_48_0_bit|DV_I_50_0_bit|DV_I_52_0_bit));
	if (mask & (DV_I_47_0_bit|DV_I_49_0_bit|DV_I_51_0_bit))
		mask &= ((0-(((W[48]^W[50])>>29)&1)) | ~(DV_I_47_0_bit|DV_I_49_0_bit|DV_I_51_0_bit));
	if (mask & (DV_I_46_0_bit|DV_I_48_0_bit|DV_I_50_0_bit))
		mask &= ((0-(((W[47]^W[49])>>29)&1)) | ~(DV_I_46_0_bit|DV_I_48_0_bit|DV_I_50_0_bit));
	if (mask & (DV_I_45_0_bit|DV_I_47_0_bit|DV_I_49_0_bit))
		mask &= ((0-(((W[46]^W[48])>>29)&1)) | ~(DV_I_45_0_bit|DV_I_47_0_bit|DV_I_49_0_bit));
	mask &= ((((W[45]^W[47])&(1<<6))-(1<<6)) | ~(DV_I_47_2_bit|DV_I_49_2_bit|DV_I_51_2_bit));
	if (mask & (DV_I_44_0_bit|DV_I_46_0_bit|DV_I_48_0_bit))
		mask &= ((0-(((W[45]^W[47])>>29)&1)) | ~(DV_I_44_0_bit|DV_I_46_0_bit|DV_I_48_0_bit));
	mask &= (((((W[44]^W[46])>>6)&1)-1) | ~(DV_I_46_2_bit|DV_I_48_2_bit|DV_I_50_2_bit));
	if (mask & (DV_I_43_0_bit|DV_I_45_0_bit|DV_I_47_0_bit))
		mask &= ((0-(((W[44]^W[46])>>29)&1)) | ~(DV_I_43_0_bit|DV_I_45_0_bit|DV_I_47_0_bit));
	mask &= ((0-((W[41]^(W[42]>>5))&(1<<1))) | ~(DV_I_48_2_bit|DV_II_46_2_bit|DV_II_51_2_bit));
	mask &= ((0-((W[40]^(W[41]>>5))&(1<<1))) | ~(DV_I_47_2_bit|DV_I_51_2_bit|DV_II_50_2_bit));
	if (mask & (DV_I_44_0_bit|DV_I_46_0_bit|DV_II_56_0_bit))
		mask &= ((0-(((W[40]^W[42])>>4)&1)) | ~(DV_I_44_0_bit|DV_I_46_0_bit|DV_II_56_0_bit));
	mask &= ((0-((W[39]^(W[40]>>5))&(1<<1))) | ~(DV_I_46_2_bit|DV_I_50_2_bit|DV_II_49_2_bit));
	if (mask & (DV_I_43_0_bit|DV_I_45_0_bit|DV_II_55_0_bit))
		mask &= ((0-(((W[39]^W[41])>>4)&1)) | ~(DV_I_43_0_bit|DV_I_45_0_bit|DV_II_55_0_bit));
	if (mask & (DV_I_44_0_bit|DV_II_54_0_bit|DV_II_56_0_bit))
		mask &= ((0-(((W[38]^W[40])>>4)&1)) | ~(DV_I_44_0_bit|DV_II_54_0_bit|DV_II_56_0_bit));
	if (mask & (DV_I_43_0_bit|DV_II_53_0_bit|DV_II_55_0_bit))
		mask &= ((0-(((W[37]^W[39])>>4)&1)) | ~(DV_I_43_0_bit|DV_II_53_0_bit|DV_II_55_0_bit));
	mask &= ((0-((W[36]^(W[37]>>5))&(1<<1))) | ~(DV_I_47_2_bit|DV_I_50_2_bit|DV_II_46_2_bit));
	if (mask & (DV_I_45_0_bit|DV_I_48_0_bit|DV_II_47_0_bit))
		mask &= (((((W[35]>>4)^(W[39]>>29))&1)-1) | ~(DV_I_45_0_bit|DV_I_48_0_bit|DV_II_47_0_bit));
	if (mask & (DV_I_48_0_bit|DV_II_48_0_bit))
		mask &= ((0-((W[63]^(W[64]>>5))&(1<<0))) | ~(DV_I_48_0_bit|DV_II_48_0_bit));
	if (mask & (DV_I_45_0_bit|DV_II_45_0_bit))
		mask &= ((0-((W[63]^(W[64]>>5))&(1<<1))) | ~(DV_I_45_0_bit|DV_II_45_0_bit));
	if (mask & (DV_I_47_0_bit|DV_II_47_0_bit))
		mask &= ((0-((W[62]^(W[63]>>5))&(1<<0))) | ~(DV_I_47_0_bit|DV_II_47_0_bit));
	if (mask & (DV_I_46_0_bit|DV_II_46_0_bit))
		mask &= ((0-((W[61]^(W[62]>>5))&(1<<0))) | ~(DV_I_46_0_bit|DV_II_46_0_bit));
	mask &= ((0-((W[61]^(W[62]>>5))&(1<<2))) | ~(DV_I_46_2_bit|DV_II_46_2_bit));
	if (mask & (DV_I_45_0_bit|DV_II_45_0_bit))
		mask &= ((0-((W[60]^(W[61]>>5))&(1<<0))) | ~(DV_I_45_0_bit|DV_II_45_0_bit));
	if (mask & (DV_II_51_0_bit|DV_II_54_0_bit))
		mask &= (((((W[58]^W[59])>>29)&1)-1) | ~(DV_II_51_0_bit|DV_II_54_0_bit));
	if (mask & (DV_II_50_0_bit|DV_II_53_0_bit))
		mask &= (((((W[57]^W[58])>>29)&1)-1) | ~(DV_II_50_0_bit|DV_II_53_0_bit));
	if (mask & (DV_II_52_0_bit|DV_II_54_0_bit))
		mask &= ((((W[56]^(W[59]>>25))&(1<<4))-(1<<4)) | ~(DV_II_52_0_bit|DV_II_54_0_bit));
	if (mask & (DV_II_51_0_bit|DV_II_52_0_bit))
		mask &= ((0-(((W[56]^W[59])>>29)&1)) | ~(DV_II_51_0_bit|DV_II_52_0_bit));
	if (mask & (DV_II_49_0_bit|DV_II_52_0_bit))
		mask &= (((((W[56]^W[57])>>29)&1)-1) | ~(DV_II_49_0_bit|DV_II_52_0_bit));
	if (mask & (DV_II_51_0_bit|DV_II_53_0_bit))
		mask &= ((((W[55]^(W[58]>>25))&(1<<4))-(1<<4)) | ~(DV_II_51_0_bit|DV_II_53_0_bit));
	if (mask & (DV_II_50_0_bit|DV_II_52_0_bit))
		mask &= ((((W[54]^(W[57]>>25))&(1<<4))-(1<<4)) | ~(DV_II_50_0_bit|DV_II_52_0_bit));
	if (mask & (DV_II_49_0_bit|DV_II_51_0_bit))
		mask &= ((((W[53]^(W[56]>>25))&(1<<4))-(1<<4)) | ~(DV_II_49_0_bit|DV_II_51_0_bit));
	mask &= ((((W[51]^(W[50]>>5))&(1<<1))-(1<<1)) | ~(DV_I_50_2_bit|DV_II_46_2_bit));
	mask &= ((((W[48]^W[50])&(1<<6))-(1<<6)) | ~(DV_I_50_2_bit|DV_II_46_2_bit));
	if (mask & (DV_I_51_0_bit|DV_I_52_0_bit))
		mask &= ((0-(((W[48]^W[55])>>29)&1)) | ~(DV_I_51_0_bit|DV_I_52_0_bit));
	mask &= ((((W[47]^W[49])&(1<<6))-(1<<6)) | ~(DV_I_49_2_bit|DV_I_51_2_bit));
	mask &= ((((W[48]^(W[47]>>5))&(1<<1))-(1<<1)) | ~(DV_I_47_2_bit|DV_II_51_2_bit));
	mask &= ((((W[46]^W[48])&(1<<6))-(1<<6)) | ~(DV_I_48_2_bit|DV_I_50_2_bit));
	mask &= ((((W[47]^(W[46]>>5))&(1<<1))-(1<<1)) | ~(DV_I_46_2_bit|DV_II_50_2_bit));
	mask &= ((0-((W[44]^(W[45]>>5))&(1<<1))) | ~(DV_I_51_2_bit|DV_II_49_2_bit));
	mask &= ((((W[43]^W[45])&(1<<6))-(1<<6)) | ~(DV_I_47_2_bit|DV_I_49_2_bit));
	mask &= (((((W[42]^W[44])>>6)&1)-1) | ~(DV_I_46_2_bit|DV_I_48_2_bit));
	mask &= ((((W[43]^(W[42]>>5))&(1<<1))-(1<<1)) | ~(DV_II_46_2_bit|DV_II_51_2_bit));
	mask &= ((((W[42]^(W[41]>>5))&(1<<1))-(1<<1)) | ~(DV_I_51_2_bit|DV_II_50_2_bit));
	mask &= ((((W[41]^(W[40]>>5))&(1<<1))-(1<<1)) | ~(DV_I_50_2_bit|DV_II_49_2_bit));
	if (mask & (DV_I_52_0_bit|DV_II_51_0_bit))
		mask &= ((((W[39]^(W[43]>>25))&(1<<4))-(1<<4)) | ~(DV_I_52_0_bit|DV_II_51_0_bit));
	if (mask & (DV_I_51_0_bit|DV_II_50_0_bit))
		mask &= ((((W[38]^(W[42]>>25))&(1<<4))-(1<<4)) | ~(DV_I_51_0_bit|DV_II_50_0_bit));
	if (mask & (DV_I_48_2_bit|DV_I_51_2_bit))
		mask &= ((0-((W[37]^(W[38]>>5))&(1<<1))) | ~(DV_I_48_2_bit|DV_I_51_2_bit));
	if (mask & (DV_I_50_0_bit|DV_II_49_0_bit))
		mask &= ((((W[37]^(W[41]>>25))&(1<<4))-(1<<4)) | ~(DV_I_50_0_bit|DV_II_49_0_bit));
	if (mask & (DV_II_52_0_bit|DV_II_54_0_bit))
		mask &= ((0-((W[36]^W[38])&(1<<4))) | ~(DV_II_52_0_bit|DV_II_54_0_bit));
	mask &= ((0-((W[35]^(W[36]>>5))&(1<<1))) | ~(DV_I_46_2_bit|DV_I_49_2_bit));
	if (mask & (DV_I_51_0_bit|DV_II_47_0_bit))
		mask &= ((((W[35]^(W[39]>>25))&(1<<3))-(1<<3)) | ~(DV_I_51_0_bit|DV_II_47_0_bit));
if (mask) {

	if (mask & DV_I_43_0_bit)
		 if (
			    !((W[61]^(W[62]>>5)) & (1<<1))
			 || !(!((W[59]^(W[63]>>25)) & (1<<5)))
			 || !((W[58]^(W[63]>>30)) & (1<<0))
		 )  mask &= ~DV_I_43_0_bit;
	if (mask & DV_I_44_0_bit)
		 if (
			    !((W[62]^(W[63]>>5)) & (1<<1))
			 || !(!((W[60]^(W[64]>>25)) & (1<<5)))
			 || !((W[59]^(W[64]>>30)) & (1<<0))
		 )  mask &= ~DV_I_44_0_bit;
	if (mask & DV_I_46_2_bit)
		mask &= ((~((W[40]^W[42])>>2)) | ~DV_I_46_2_bit);
	if (mask & DV_I_47_2_bit)
		 if (
			    !((W[62]^(W[63]>>5)) & (1<<2))
			 || !(!((W[41]^W[43]) & (1<<6)))
		 )  mask &= ~DV_I_47_2_bit;
	if (mask & DV_I_48_2_bit)
		 if (
			    !((W[63]^(W[64]>>5)) & (1<<2))
			 || !(!((W[48]^(W[49]<<5)) & (1<<6)))
		 )  mask &= ~DV_I_48_2_bit;
	if (mask & DV_I_49_2_bit)
		 if (
			    !(!((W[49]^(W[50]<<5)) & (1<<6)))
			 || !((W[42]^W[50]) & (1<<1))
			 || !(!((W[39]^(W[40]<<5)) & (1<<6)))
			 || !((W[38]^W[40]) & (1<<1))
		 )  mask &= ~DV_I_49_2_bit;
	if (mask & DV_I_50_0_bit)
		mask &= ((((W[36]^W[37])<<7)) | ~DV_I_50_0_bit);
	if (mask & DV_I_50_2_bit)
		mask &= ((((W[43]^W[51])<<11)) | ~DV_I_50_2_bit);
	if (mask & DV_I_51_0_bit)
		mask &= ((((W[37]^W[38])<<9)) | ~DV_I_51_0_bit);
	if (mask & DV_I_51_2_bit)
		 if (
			    !(!((W[51]^(W[52]<<5)) & (1<<6)))
			 || !(!((W[49]^W[51]) & (1<<6)))
			 || !(!((W[37]^(W[37]>>5)) & (1<<1)))
			 || !(!((W[35]^(W[39]>>25)) & (1<<5)))
		 )  mask &= ~DV_I_51_2_bit;
	if (mask & DV_I_52_0_bit)
		mask &= ((((W[38]^W[39])<<11)) | ~DV_I_52_0_bit);
	if (mask & DV_II_46_2_bit)
		mask &= ((((W[47]^W[51])<<17)) | ~DV_II_46_2_bit);
	if (mask & DV_II_48_0_bit)
		 if (
			    !(!((W[36]^(W[40]>>25)) & (1<<3)))
			 || !((W[35]^(W[40]<<2)) & (1<<30))
		 )  mask &= ~DV_II_48_0_bit;
	if (mask & DV_II_49_0_bit)
		 if (
			    !(!((W[37]^(W[41]>>25)) & (1<<3)))
			 || !((W[36]^(W[41]<<2)) & (1<<30))
		 )  mask &= ~DV_II_49_0_bit;
	if (mask & DV_II_49_2_bit)
		 if (
			    !(!((W[53]^(W[54]<<5)) & (1<<6)))
			 || !(!((W[51]^W[53]) & (1<<6)))
			 || !((W[50]^W[54]) & (1<<1))
			 || !(!((W[45]^(W[46]<<5)) & (1<<6)))
			 || !(!((W[37]^(W[41]>>25)) & (1<<5)))
			 || !((W[36]^(W[41]>>30)) & (1<<0))
		 )  mask &= ~DV_II_49_2_bit;
	if (mask & DV_II_50_0_bit)
		 if (
			    !((W[55]^W[58]) & (1<<29))
			 || !(!((W[38]^(W[42]>>25)) & (1<<3)))
			 || !((W[37]^(W[42]<<2)) & (1<<30))
		 )  mask &= ~DV_II_50_0_bit;
	if (mask & DV_II_50_2_bit)
		 if (
			    !(!((W[54]^(W[55]<<5)) & (1<<6)))
			 || !(!((W[52]^W[54]) & (1<<6)))
			 || !((W[51]^W[55]) & (1<<1))
			 || !((W[45]^W[47]) & (1<<1))
			 || !(!((W[38]^(W[42]>>25)) & (1<<5)))
			 || !((W[37]^(W[42]>>30)) & (1<<0))
		 )  mask &= ~DV_II_50_2_bit;
	if (mask & DV_II_51_0_bit)
		 if (
			    !(!((W[39]^(W[43]>>25)) & (1<<3)))
			 || !((W[38]^(W[43]<<2)) & (1<<30))
		 )  mask &= ~DV_II_51_0_bit;
	if (mask & DV_II_51_2_bit)
		 if (
			    !(!((W[55]^(W[56]<<5)) & (1<<6)))
			 || !(!((W[53]^W[55]) & (1<<6)))
			 || !((W[52]^W[56]) & (1<<1))
			 || !((W[46]^W[48]) & (1<<1))
			 || !(!((W[39]^(W[43]>>25)) & (1<<5)))
			 || !((W[38]^(W[43]>>30)) & (1<<0))
		 )  mask &= ~DV_II_51_2_bit;
	if (mask & DV_II_52_0_bit)
		 if (
			    !(!((W[59]^W[60]) & (1<<29)))
			 || !(!((W[40]^(W[44]>>25)) & (1<<3)))
			 || !(!((W[40]^(W[44]>>25)) & (1<<4)))
			 || !((W[39]^(W[44]<<2)) & (1<<30))
		 )  mask &= ~DV_II_52_0_bit;
	if (mask & DV_II_53_0_bit)
		 if (
			    !((W[58]^W[61]) & (1<<29))
			 || !(!((W[57]^(W[61]>>25)) & (1<<4)))
			 || !(!((W[41]^(W[45]>>25)) & (1<<3)))
			 || !(!((W[41]^(W[45]>>25)) & (1<<4)))
		 )  mask &= ~DV_II_53_0_bit;
	if (mask & DV_II_54_0_bit)
		 if (
			    !(!((W[58]^(W[62]>>25)) & (1<<4)))
			 || !(!((W[42]^(W[46]>>25)) & (1<<3)))
			 || !(!((W[42]^(W[46]>>25)) & (1<<4)))
		 )  mask &= ~DV_II_54_0_bit;
	if (mask & DV_II_55_0_bit)
		 if (
			    !(!((W[59]^(W[63]>>25)) & (1<<4)))
			 || !(!((W[57]^(W[59]>>25)) & (1<<4)))
			 || !(!((W[43]^(W[47]>>25)) & (1<<3)))
			 || !(!((W[43]^(W[47]>>25)) & (1<<4)))
		 )  mask &= ~DV_II_55_0_bit;
	if (mask & DV_II_56_0_bit)
		 if (
			    !(!((W[60]^(W[64]>>25)) & (1<<4)))
			 || !(!((W[44]^(W[48]>>25)) & (1<<3)))
			 || !(!((W[44]^(W[48]>>25)) & (1<<4)))
		 )  mask &= ~DV_II_56_0_bit;
}

	dvmask[0]=mask;
}