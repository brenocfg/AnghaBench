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
typedef  int u_int8_t ;
struct dos_partition {int dp_ssect; int dp_esect; int /*<<< orphan*/  dp_size; int /*<<< orphan*/  dp_start; int /*<<< orphan*/  dp_ehd; scalar_t__ dp_ecyl; scalar_t__ dp_typ; int /*<<< orphan*/  dp_shd; scalar_t__ dp_scyl; int /*<<< orphan*/  dp_flag; } ;
struct TYPE_2__ {int def; char* tok; } ;

/* Variables and functions */
 int DOSPARTOFF ; 
 int NDOSPART ; 
 size_t OFF_DRIVE ; 
 size_t OFF_FLAGS ; 
 size_t OFF_OPT ; 
 size_t OFF_SERIAL ; 
 int OFF_TICKS ; 
 int b0_ver ; 
 int boot0version (int*) ; 
 int cv2 (int*) ; 
 char* fmt0 ; 
 char* fmt1 ; 
 int nopt ; 
 TYPE_1__* opttbl ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_bell (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
display_mbr(u_int8_t *mbr)
{
    struct dos_partition *part;
    int i, version;

    part = (struct dos_partition *)(mbr + DOSPARTOFF);
    printf(fmt0);
    for (i = 0; i < NDOSPART; i++)
	if (part[i].dp_typ)
	    printf(fmt1, 1 + i, part[i].dp_flag,
		part[i].dp_scyl + ((part[i].dp_ssect & 0xc0) << 2),
		part[i].dp_shd, part[i].dp_ssect & 0x3f, part[i].dp_typ,
                part[i].dp_ecyl + ((part[i].dp_esect & 0xc0) << 2),
                part[i].dp_ehd, part[i].dp_esect & 0x3f, part[i].dp_start,
                part[i].dp_size);
    printf("\n");
    version = boot0version(mbr);
    printf("version=%d.%d  drive=0x%x  mask=0x%x  ticks=%u",
	version >> 8, version & 0xff, mbr[OFF_DRIVE],
	mbr[OFF_FLAGS] & 0xf, cv2(mbr + OFF_TICKS));
    set_bell(mbr, 0, 1);
    printf("\noptions=");
    for (i = 0; i < nopt; i++) {
	if (i)
	    printf(",");
	if (!(mbr[OFF_FLAGS] & 1 << (7 - i)) ^ opttbl[i].def)
	    printf("no");
	printf("%s", opttbl[i].tok);
    }
    printf("\n");
    if (b0_ver == 2)
	printf("volume serial ID %02x%02x-%02x%02x\n",
		mbr[OFF_SERIAL], mbr[OFF_SERIAL+1],
		mbr[OFF_SERIAL+2], mbr[OFF_SERIAL+3]);
    printf("default_selection=F%d (", mbr[OFF_OPT] + 1);
    if (mbr[OFF_OPT] < 4)
	printf("Slice %d", mbr[OFF_OPT] + 1);
    else if (mbr[OFF_OPT] == 4)
	printf("Drive 1");
    else
	printf("PXE");
    printf(")\n");
}