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

/* Variables and functions */
#define  IWI_RATE_DS1 139 
#define  IWI_RATE_DS11 138 
#define  IWI_RATE_DS2 137 
#define  IWI_RATE_DS5 136 
#define  IWI_RATE_OFDM12 135 
#define  IWI_RATE_OFDM18 134 
#define  IWI_RATE_OFDM24 133 
#define  IWI_RATE_OFDM36 132 
#define  IWI_RATE_OFDM48 131 
#define  IWI_RATE_OFDM54 130 
#define  IWI_RATE_OFDM6 129 
#define  IWI_RATE_OFDM9 128 

__attribute__((used)) static int
iwi_cvtrate(int iwirate)
{
	switch (iwirate) {
	case IWI_RATE_DS1:	return 2;
	case IWI_RATE_DS2:	return 4;
	case IWI_RATE_DS5:	return 11;
	case IWI_RATE_DS11:	return 22;
	case IWI_RATE_OFDM6:	return 12;
	case IWI_RATE_OFDM9:	return 18;
	case IWI_RATE_OFDM12:	return 24;
	case IWI_RATE_OFDM18:	return 36;
	case IWI_RATE_OFDM24:	return 48;
	case IWI_RATE_OFDM36:	return 72;
	case IWI_RATE_OFDM48:	return 96;
	case IWI_RATE_OFDM54:	return 108;
	}
	return 0;
}