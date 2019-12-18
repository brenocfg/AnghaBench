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
struct flash_sec_info {TYPE_1__* fsec_entry; } ;
struct flash_img_attri {int img_offset; int img_size; int img_type; int optype; void* skip_image; } ;
struct firmware {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  pad_size; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 void* FALSE ; 
 void* HOST_32 (int /*<<< orphan*/ ) ; 
#define  IMG_BIOS 137 
#define  IMG_FCOE 136 
#define  IMG_FCOEBIOS 135 
#define  IMG_FCOE_BAK 134 
#define  IMG_ISCSI 133 
#define  IMG_ISCSI_BAK 132 
#define  IMG_NCSI 131 
#define  IMG_PHY 130 
#define  IMG_PXEBIOS 129 
#define  IMG_REDBOOT 128 
 int /*<<< orphan*/  IS_BE3 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SH (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  oce_img_flashing_required (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  oce_phy_flashing_required (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void oce_fill_flash_img_data(POCE_SOFTC sc, const struct flash_sec_info * fsec,
				struct flash_img_attri *pimg, int i,
				const struct firmware *fw, int bin_offset)
{
	if (IS_SH(sc)) {
		pimg->img_offset = HOST_32(fsec->fsec_entry[i].offset);
		pimg->img_size   = HOST_32(fsec->fsec_entry[i].pad_size);
	}

	pimg->img_type = HOST_32(fsec->fsec_entry[i].type);
	pimg->skip_image = FALSE;
	switch (pimg->img_type) {
		case IMG_ISCSI:
			pimg->optype = 0;
			if (IS_BE3(sc)) {
				pimg->img_offset = 2097152;
				pimg->img_size   = 2097152;
			}
			break;
		case IMG_REDBOOT:
			pimg->optype = 1;
			if (IS_BE3(sc)) {
				pimg->img_offset = 262144;
				pimg->img_size   = 1048576;
			}
			if (!oce_img_flashing_required(sc, fw->data,
						pimg->optype,
						pimg->img_offset,
						pimg->img_size,
						bin_offset))
				pimg->skip_image = TRUE;
			break;
		case IMG_BIOS:
			pimg->optype = 2;
			if (IS_BE3(sc)) {
				pimg->img_offset = 12582912;
				pimg->img_size   = 524288;
			}
			break;
		case IMG_PXEBIOS:
			pimg->optype = 3;
			if (IS_BE3(sc)) {
				pimg->img_offset =  13107200;
				pimg->img_size   = 524288;
			}
			break;
		case IMG_FCOEBIOS:
			pimg->optype = 8;
			if (IS_BE3(sc)) {
				pimg->img_offset = 13631488;
				pimg->img_size   = 524288;
			}
			break;
		case IMG_ISCSI_BAK:
			pimg->optype = 9;
			if (IS_BE3(sc)) {
				pimg->img_offset = 4194304;
				pimg->img_size   = 2097152;
			}
			break;
		case IMG_FCOE:
			pimg->optype = 10;
			if (IS_BE3(sc)) {
				pimg->img_offset = 6291456;
				pimg->img_size   = 2097152;
			}
			break;
		case IMG_FCOE_BAK:
			pimg->optype = 11;
			if (IS_BE3(sc)) {
				pimg->img_offset = 8388608;
				pimg->img_size   = 2097152;
			}
			break;
		case IMG_NCSI:
			pimg->optype = 13;
			if (IS_BE3(sc)) {
				pimg->img_offset = 15990784;
				pimg->img_size   = 262144;
			}
			break;
		case IMG_PHY:
			pimg->optype = 99;
			if (IS_BE3(sc)) {
				pimg->img_offset = 1310720;
				pimg->img_size   = 262144;
			}
			if (!oce_phy_flashing_required(sc))
				pimg->skip_image = TRUE;
			break;
		default:
			pimg->skip_image = TRUE;
			break;
	}

}