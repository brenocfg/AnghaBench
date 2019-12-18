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
typedef  int uint16_t ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int ANAR_10 ; 
 int ANAR_10_FD ; 
 int ANAR_TX ; 
 int ANAR_TX_FD ; 
#define  IFM_1000_T 131 
#define  IFM_100_TX 130 
#define  IFM_10_T 129 
#define  IFM_AUTO 128 
 int IFM_FDX ; 
 int const IFM_SUBTYPE (int) ; 

__attribute__((used)) static uint16_t
atphy_anar(struct ifmedia_entry *ife)
{
	uint16_t anar;

	anar = 0;
	switch (IFM_SUBTYPE(ife->ifm_media)) {
	case IFM_AUTO:
		anar |= ANAR_TX_FD | ANAR_TX | ANAR_10_FD | ANAR_10;
		return (anar);
	case IFM_1000_T:
		return (anar);
	case IFM_100_TX:
		anar |= ANAR_TX;
		break;
	case IFM_10_T:
		anar |= ANAR_10;
		break;
	default:
		return (0);
	}

	if ((ife->ifm_media & IFM_FDX) != 0) {
		if (IFM_SUBTYPE(ife->ifm_media) == IFM_100_TX)
			anar |= ANAR_TX_FD;
		else
			anar |= ANAR_10_FD;
	}

	return (anar);
}