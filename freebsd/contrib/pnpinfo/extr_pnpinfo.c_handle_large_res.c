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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
#define  PNP_TAG_ID_ANSI 134 
#define  PNP_TAG_ID_UNICODE 133 
#define  PNP_TAG_LARGE_RESERVED 132 
#define  PNP_TAG_LARGE_VENDOR 131 
#define  PNP_TAG_MEMORY32_FIXED 130 
#define  PNP_TAG_MEMORY32_RANGE 129 
#define  PNP_TAG_MEMORY_RANGE 128 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  report_memory_info (int) ; 

void
handle_large_res(u_char *resinfo, int item, int len)
{
    int i;

    DEB(printf("*** Large ITEM %d len %d found\n", item, len));
    switch (item) {
    case PNP_TAG_MEMORY_RANGE:
	report_memory_info(resinfo[0]);
	printf("Memory range minimum address: 0x%x\n",
		(resinfo[1] << 8) + (resinfo[2] << 16));
	printf("Memory range maximum address: 0x%x\n",
		(resinfo[3] << 8) + (resinfo[4] << 16));
	printf("Memory range base alignment: 0x%x\n",
		(i = (resinfo[5] + (resinfo[6] << 8))) ? i : (1 << 16));
	printf("Memory range length: 0x%x\n",
		(resinfo[7] + (resinfo[8] << 8)) * 256);
	break;
    case PNP_TAG_ID_ANSI:
	printf("Device Description: ");

	for (i = 0; i < len; i++) {
	    if (resinfo[i]) /* XXX */
		printf("%c", resinfo[i]);
	}
	printf("\n");
	break;
    case PNP_TAG_ID_UNICODE:
	printf("ID String Unicode Detected (Undefined)\n");
	break;
    case PNP_TAG_LARGE_VENDOR:
	printf("Large Vendor Defined Detected\n");
	break;
    case PNP_TAG_MEMORY32_RANGE:
	printf("32bit Memory Range Desc Unimplemented\n");
	break;
    case PNP_TAG_MEMORY32_FIXED:
	printf("32bit Fixed Location Desc Unimplemented\n");
	break;
#ifdef DIAGNOSTIC
    case PNP_TAG_LARGE_RESERVED:
	printf("Large Reserved Tag Detected\n");
	break;
#endif
    }
}