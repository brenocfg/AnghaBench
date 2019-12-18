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
struct ieee80211_regdomain {int regdomain; int /*<<< orphan*/  country; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRY_FRANCE ; 
 int /*<<< orphan*/  CTRY_FRANCE2 ; 
 int /*<<< orphan*/  CTRY_SPAIN ; 
 int DOMAIN_CODE_AUS ; 
 int DOMAIN_CODE_DGT ; 
 int DOMAIN_CODE_ETSI_131 ; 
 int DOMAIN_CODE_FCC ; 
 int DOMAIN_CODE_FRANCE ; 
 int DOMAIN_CODE_IC ; 
 int DOMAIN_CODE_MKK ; 
 int DOMAIN_CODE_SPAIN ; 
#define  SKU_APAC 138 
#define  SKU_APAC2 137 
#define  SKU_APAC3 136 
#define  SKU_CA 135 
#define  SKU_ETSI 134 
#define  SKU_ETSI2 133 
#define  SKU_ETSI3 132 
#define  SKU_FCC 131 
#define  SKU_FCC3 130 
#define  SKU_JAPAN 129 
#define  SKU_ROW 128 

__attribute__((used)) static int
mwl_map2regioncode(const struct ieee80211_regdomain *rd)
{
	switch (rd->regdomain) {
	case SKU_FCC:
	case SKU_FCC3:
		return DOMAIN_CODE_FCC;
	case SKU_CA:
		return DOMAIN_CODE_IC;
	case SKU_ETSI:
	case SKU_ETSI2:
	case SKU_ETSI3:
		if (rd->country == CTRY_SPAIN)
			return DOMAIN_CODE_SPAIN;
		if (rd->country == CTRY_FRANCE || rd->country == CTRY_FRANCE2)
			return DOMAIN_CODE_FRANCE;
		/* XXX force 1.3.1 radar type */
		return DOMAIN_CODE_ETSI_131;
	case SKU_JAPAN:
		return DOMAIN_CODE_MKK;
	case SKU_ROW:
		return DOMAIN_CODE_DGT;	/* Taiwan */
	case SKU_APAC:
	case SKU_APAC2:
	case SKU_APAC3:
		return DOMAIN_CODE_AUS;	/* Australia */
	}
	/* XXX KOREA? */
	return DOMAIN_CODE_FCC;			/* XXX? */
}