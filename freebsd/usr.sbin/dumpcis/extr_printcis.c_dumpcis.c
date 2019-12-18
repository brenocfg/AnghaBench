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
struct tuple_list {struct tuple* tuples; struct tuple_list* next; } ;
struct tuple {int code; int length; int* data; struct tuple* next; } ;

/* Variables and functions */
#define  CIS_ALTSTR 151 
#define  CIS_BAR 150 
#define  CIS_CHECKSUM 149 
#define  CIS_CONFIG 148 
#define  CIS_CONFIG_CB 147 
#define  CIS_CONF_MAP 146 
#define  CIS_CONF_MAP_CB 145 
#define  CIS_DEVICEGEO 144 
#define  CIS_DEVICEGEO_A 143 
#define  CIS_DEVICE_OA 142 
#define  CIS_DEVICE_OC 141 
#define  CIS_FUNC_EXT 140 
#define  CIS_FUNC_ID 139 
#define  CIS_INFO_V1 138 
#define  CIS_JEDEC_A 137 
#define  CIS_JEDEC_C 136 
#define  CIS_LONGLINK_A 135 
#define  CIS_LONGLINK_C 134 
#define  CIS_LONGLINK_MFC 133 
#define  CIS_MANUF_ID 132 
#define  CIS_MEM_ATTR 131 
#define  CIS_MEM_COMMON 130 
#define  CIS_ORG 129 
#define  CIS_VERS_2 128 
 int /*<<< orphan*/  dump_bar (int*,int) ; 
 int /*<<< orphan*/  dump_cis_config (struct tuple*) ; 
 int /*<<< orphan*/  dump_config_map (struct tuple*) ; 
 int /*<<< orphan*/  dump_device_desc (int*,int,char*) ; 
 int /*<<< orphan*/  dump_device_geo (int*,int) ; 
 int /*<<< orphan*/  dump_disk_ext (int*,int) ; 
 int /*<<< orphan*/  dump_func_id (int*) ; 
 int /*<<< orphan*/  dump_info_v1 (int*,int) ; 
 int /*<<< orphan*/  dump_info_v2 (int*,int) ; 
 int /*<<< orphan*/  dump_longlink_mfc (int*,int) ; 
 int /*<<< orphan*/  dump_network_ext (int*,int) ; 
 int /*<<< orphan*/  dump_org (int*,int) ; 
 int /*<<< orphan*/  dump_other_cond (int*,int) ; 
 int /*<<< orphan*/  dump_serial_ext (int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int tpl16 (int*) ; 
 int tpl32 (int*) ; 
 char* tuple_name (int) ; 

void
dumpcis(struct tuple_list *tlist)
{
	struct tuple *tp;
	struct tuple_list *tl;
	int     count = 0, sz, ad, i;
	u_char *p;
	int func = 0;

	for (tl = tlist; tl; tl = tl->next)
		for (tp = tl->tuples; tp; tp = tp->next) {
			printf("Tuple #%d, code = 0x%x (%s), length = %d\n",
			    ++count, tp->code, tuple_name(tp->code), tp->length);
			p = tp->data;
			sz = tp->length;
			ad = 0;
			while (sz > 0) {
				printf("    %03x: ", ad);
				for (i = 0; i < ((sz < 16) ? sz : 16); i++)
					printf(" %02x", p[i]);
				printf("\n");
				sz -= 16;
				p += 16;
				ad += 16;
			}
			switch (tp->code) {
			default:
				break;
			case CIS_MEM_COMMON:	/* 0x01 */
				dump_device_desc(tp->data, tp->length, "Common");
				break;
			case CIS_CONF_MAP_CB:	/* 0x04 */
				dump_config_map(tp);
				break;
			case CIS_CONFIG_CB:	/* 0x05 */
				dump_cis_config(tp);
				break;
			case CIS_LONGLINK_MFC:	/* 0x06 */
				dump_longlink_mfc(tp->data, tp->length);
				break;
			case CIS_BAR:		/* 0x07 */
				dump_bar(tp->data, tp->length);
				break;
			case CIS_CHECKSUM:	/* 0x10 */
				printf("\tChecksum from offset %d, length %d, value is 0x%x\n",
				       tpl16(tp->data),
				       tpl16(tp->data + 2),
				       tp->data[4]);
				break;
			case CIS_LONGLINK_A:	/* 0x11 */
				printf("\tLong link to attribute memory, address 0x%x\n",
				       tpl32(tp->data));
				break;
			case CIS_LONGLINK_C:	/* 0x12 */
				printf("\tLong link to common memory, address 0x%x\n",
				       tpl32(tp->data));
				break;	
			case CIS_INFO_V1:	/* 0x15 */
				dump_info_v1(tp->data, tp->length);
				break;
			case CIS_ALTSTR:	/* 0x16 */
				break;
			case CIS_MEM_ATTR:	/* 0x17 */
				dump_device_desc(tp->data, tp->length, "Attribute");
				break;
			case CIS_JEDEC_C:	/* 0x18 */
			case CIS_JEDEC_A:	/* 0x19 */
				break;
			case CIS_CONF_MAP:	/* 0x1A */
				dump_config_map(tp);
				break;
			case CIS_CONFIG:	/* 0x1B */
				dump_cis_config(tp);
				break;
			case CIS_DEVICE_OC:	/* 0x1C */
			case CIS_DEVICE_OA:	/* 0x1D */
				dump_other_cond(tp->data, tp->length);
				break;
			case CIS_DEVICEGEO:	/* 0x1E */
			case CIS_DEVICEGEO_A:	/* 0x1F */
				dump_device_geo(tp->data, tp->length);
				break;
			case CIS_MANUF_ID:	/* 0x20 */
				printf("\tPCMCIA ID = 0x%x, OEM ID = 0x%x\n",
				       tpl16(tp->data),
				       tpl16(tp->data + 2));
				break;
			case CIS_FUNC_ID:	/* 0x21 */
				func = tp->data[0];
				dump_func_id(tp->data);
				break;
			case CIS_FUNC_EXT:	/* 0x22 */
				switch (func) {
				case 2:
					dump_serial_ext(tp->data, tp->length);
					break;
				case 4:
					dump_disk_ext(tp->data, tp->length);
					break;
				case 6:
					dump_network_ext(tp->data, tp->length);
					break;
				}
				break;
			case CIS_VERS_2:	/* 0x40 */
				dump_info_v2(tp->data, tp->length);
				break;
			case CIS_ORG:		/* 0x46 */
				dump_org(tp->data, tp->length);
				break;
			}
		}
}