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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  RPL_LUNDATA_ATYP_EXTLUN 131 
#define  RPL_LUNDATA_ATYP_FLAT 130 
 int RPL_LUNDATA_ATYP_MASK ; 
#define  RPL_LUNDATA_ATYP_PERIPH 129 
 int RPL_LUNDATA_EXT_EAM_MASK ; 
#define  RPL_LUNDATA_EXT_EAM_NOT_SPEC 128 
 int RPL_LUNDATA_EXT_LEN_MASK ; 
 int /*<<< orphan*/  be64enc (int*,int /*<<< orphan*/ ) ; 

uint32_t
ctl_decode_lun(uint64_t encoded)
{
	uint8_t lun[8];
	uint32_t result = 0xffffffff;

	be64enc(lun, encoded);
	switch (lun[0] & RPL_LUNDATA_ATYP_MASK) {
	case RPL_LUNDATA_ATYP_PERIPH:
		if ((lun[0] & 0x3f) == 0 && lun[2] == 0 && lun[3] == 0 &&
		    lun[4] == 0 && lun[5] == 0 && lun[6] == 0 && lun[7] == 0)
			result = lun[1];
		break;
	case RPL_LUNDATA_ATYP_FLAT:
		if (lun[2] == 0 && lun[3] == 0 && lun[4] == 0 && lun[5] == 0 &&
		    lun[6] == 0 && lun[7] == 0)
			result = ((lun[0] & 0x3f) << 8) + lun[1];
		break;
	case RPL_LUNDATA_ATYP_EXTLUN:
		switch (lun[0] & RPL_LUNDATA_EXT_EAM_MASK) {
		case 0x02:
			switch (lun[0] & RPL_LUNDATA_EXT_LEN_MASK) {
			case 0x00:
				result = lun[1];
				break;
			case 0x10:
				result = (lun[1] << 16) + (lun[2] << 8) +
				    lun[3];
				break;
			case 0x20:
				if (lun[1] == 0 && lun[6] == 0 && lun[7] == 0)
					result = (lun[2] << 24) +
					    (lun[3] << 16) + (lun[4] << 8) +
					    lun[5];
				break;
			}
			break;
		case RPL_LUNDATA_EXT_EAM_NOT_SPEC:
			result = 0xffffffff;
			break;
		}
		break;
	}
	return (result);
}