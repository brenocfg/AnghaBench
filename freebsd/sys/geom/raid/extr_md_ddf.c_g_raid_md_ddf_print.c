#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct ddf_vuc_record {int* VD_GUID; } ;
struct ddf_vdc_record {int* VD_GUID; int /*<<< orphan*/ * Physical_Disk_Sequence; int /*<<< orphan*/  Primary_Element_Count; int /*<<< orphan*/  MDF_Constant_Generation_Method; int /*<<< orphan*/  MDF_Parity_Generator_Polynomial; int /*<<< orphan*/  MDF_Parity_Disks; int /*<<< orphan*/  BG_Rate; int /*<<< orphan*/  Cache_Flags; int /*<<< orphan*/ * Associated_Spares; int /*<<< orphan*/  Rotate_Parity_count; int /*<<< orphan*/  Block_Size; int /*<<< orphan*/  VD_Size; int /*<<< orphan*/  Block_Count; int /*<<< orphan*/  Secondary_RAID_Level; int /*<<< orphan*/  Secondary_Element_Seq; int /*<<< orphan*/  Secondary_Element_Count; int /*<<< orphan*/  RLQ; int /*<<< orphan*/  Primary_RAID_Level; int /*<<< orphan*/  Stripe_Size; int /*<<< orphan*/  Sequence_Number; int /*<<< orphan*/  Timestamp; int /*<<< orphan*/  Signature; } ;
struct ddf_sa_record {TYPE_10__* entry; int /*<<< orphan*/  Populated_SAEs; int /*<<< orphan*/  MAX_SAE_Supported; int /*<<< orphan*/  Spare_Type; int /*<<< orphan*/  Timestamp; } ;
struct ddf_meta {TYPE_11__* pdd; TYPE_9__* vdr; TYPE_5__* pdr; TYPE_3__* cdr; TYPE_1__* hdr; } ;
struct TYPE_32__ {TYPE_8__* entry; } ;
struct TYPE_31__ {int* VD_GUID; int /*<<< orphan*/  VD_Name; } ;
struct TYPE_30__ {int /*<<< orphan*/  Drive_Failures_Remaining; int /*<<< orphan*/  Init_State; int /*<<< orphan*/  VD_State; int /*<<< orphan*/  VD_Type; int /*<<< orphan*/  VD_Number; } ;
struct TYPE_29__ {int /*<<< orphan*/  Block_Size; int /*<<< orphan*/  Configured_Size; int /*<<< orphan*/  PD_State; int /*<<< orphan*/  PD_Type; int /*<<< orphan*/  PD_Reference; } ;
struct TYPE_28__ {TYPE_4__* entry; } ;
struct TYPE_27__ {int* PD_GUID; } ;
struct TYPE_26__ {int* Controller_GUID; int /*<<< orphan*/ * Product_ID; } ;
struct TYPE_25__ {int /*<<< orphan*/  Device_ID; int /*<<< orphan*/  Vendor_ID; int /*<<< orphan*/  SubDevice_ID; int /*<<< orphan*/  SubVendor_ID; } ;
struct TYPE_24__ {int* DDF_Header_GUID; int /*<<< orphan*/ * DDF_rev; } ;
struct TYPE_23__ {TYPE_2__ Controller_Type; } ;
struct TYPE_22__ {int /*<<< orphan*/  Max_Primary_Element_Entries; int /*<<< orphan*/  Vendor_Specific_Logs_Length; int /*<<< orphan*/  Vendor_Specific_Logs; int /*<<< orphan*/  Diagnostic_Space_Length; int /*<<< orphan*/  Diagnostic_Space; int /*<<< orphan*/  bbmlog_length; int /*<<< orphan*/  bbmlog_section; int /*<<< orphan*/  pdd_length; int /*<<< orphan*/  pdd_section; int /*<<< orphan*/  cr_length; int /*<<< orphan*/  cr_section; int /*<<< orphan*/  vdr_length; int /*<<< orphan*/  vdr_section; int /*<<< orphan*/  pdr_length; int /*<<< orphan*/  pdr_section; int /*<<< orphan*/  cd_length; int /*<<< orphan*/  cd_section; int /*<<< orphan*/  Configuration_Record_Length; int /*<<< orphan*/  Max_Partitions; int /*<<< orphan*/  Max_VD_Entries; int /*<<< orphan*/  Max_PD_Entries; int /*<<< orphan*/  WorkSpace_LBA; int /*<<< orphan*/  WorkSpace_Length; int /*<<< orphan*/  Secondary_Header_LBA; int /*<<< orphan*/  Primary_Header_LBA; int /*<<< orphan*/  Diskgrouping; int /*<<< orphan*/  Foreign_Flag; int /*<<< orphan*/  Open_Flag; int /*<<< orphan*/  TimeStamp; int /*<<< orphan*/  Sequence_Number; } ;
struct TYPE_21__ {int /*<<< orphan*/  Forced_PD_GUID_Flag; int /*<<< orphan*/  Forced_Ref_Flag; int /*<<< orphan*/  PD_Reference; } ;
struct TYPE_20__ {TYPE_6__* entry; int /*<<< orphan*/  Populated_PDEs; int /*<<< orphan*/  Max_PDE_Supported; } ;
struct TYPE_19__ {TYPE_7__* entry; int /*<<< orphan*/  Populated_VDEs; int /*<<< orphan*/  Max_VDE_Supported; } ;
struct TYPE_18__ {int* PD_GUID; } ;
struct TYPE_17__ {int* VD_GUID; int /*<<< orphan*/  Secondary_Element; } ;

/* Variables and functions */
#define  DDF_SA_SIGNATURE 130 
#define  DDF_VDCR_SIGNATURE 129 
#define  DDF_VUCR_SIGNATURE 128 
 size_t GET16 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET16D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET32 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET32D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET64 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET64D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET64P (struct ddf_meta*,int /*<<< orphan*/ *) ; 
 int GET8 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET8D (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GETCRNUM (struct ddf_meta*) ; 
 struct ddf_vdc_record* GETVDCPTR (struct ddf_meta*,int) ; 
 TYPE_16__* cdr ; 
 int g_raid_debug ; 
 TYPE_15__* hdr ; 
 scalar_t__ isff (int*,int) ; 
 TYPE_14__* pdd ; 
 TYPE_13__* pdr ; 
 int /*<<< orphan*/  print_guid (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_12__* vdr ; 

__attribute__((used)) static void
g_raid_md_ddf_print(struct ddf_meta *meta)
{
	struct ddf_vdc_record *vdc;
	struct ddf_vuc_record *vuc;
	struct ddf_sa_record *sa;
	uint64_t *val2;
	uint32_t val;
	int i, j, k, num, num2;

	if (g_raid_debug < 1)
		return;

	printf("********* DDF Metadata *********\n");
	printf("**** Header ****\n");
	printf("DDF_Header_GUID      ");
	print_guid(meta->hdr->DDF_Header_GUID);
	printf("\n");
	printf("DDF_rev              %8.8s\n", (char *)&meta->hdr->DDF_rev[0]);
	printf("Sequence_Number      0x%08x\n", GET32(meta, hdr->Sequence_Number));
	printf("TimeStamp            0x%08x\n", GET32(meta, hdr->TimeStamp));
	printf("Open_Flag            0x%02x\n", GET16(meta, hdr->Open_Flag));
	printf("Foreign_Flag         0x%02x\n", GET16(meta, hdr->Foreign_Flag));
	printf("Diskgrouping         0x%02x\n", GET16(meta, hdr->Diskgrouping));
	printf("Primary_Header_LBA   %ju\n", GET64(meta, hdr->Primary_Header_LBA));
	printf("Secondary_Header_LBA %ju\n", GET64(meta, hdr->Secondary_Header_LBA));
	printf("WorkSpace_Length     %u\n", GET32(meta, hdr->WorkSpace_Length));
	printf("WorkSpace_LBA        %ju\n", GET64(meta, hdr->WorkSpace_LBA));
	printf("Max_PD_Entries       %u\n", GET16(meta, hdr->Max_PD_Entries));
	printf("Max_VD_Entries       %u\n", GET16(meta, hdr->Max_VD_Entries));
	printf("Max_Partitions       %u\n", GET16(meta, hdr->Max_Partitions));
	printf("Configuration_Record_Length %u\n", GET16(meta, hdr->Configuration_Record_Length));
	printf("Max_Primary_Element_Entries %u\n", GET16(meta, hdr->Max_Primary_Element_Entries));
	printf("Controller Data      %u:%u\n", GET32(meta, hdr->cd_section), GET32(meta, hdr->cd_length));
	printf("Physical Disk        %u:%u\n", GET32(meta, hdr->pdr_section), GET32(meta, hdr->pdr_length));
	printf("Virtual Disk         %u:%u\n", GET32(meta, hdr->vdr_section), GET32(meta, hdr->vdr_length));
	printf("Configuration Recs   %u:%u\n", GET32(meta, hdr->cr_section), GET32(meta, hdr->cr_length));
	printf("Physical Disk Recs   %u:%u\n", GET32(meta, hdr->pdd_section), GET32(meta, hdr->pdd_length));
	printf("BBM Log              %u:%u\n", GET32(meta, hdr->bbmlog_section), GET32(meta, hdr->bbmlog_length));
	printf("Diagnostic Space     %u:%u\n", GET32(meta, hdr->Diagnostic_Space), GET32(meta, hdr->Diagnostic_Space_Length));
	printf("Vendor_Specific_Logs %u:%u\n", GET32(meta, hdr->Vendor_Specific_Logs), GET32(meta, hdr->Vendor_Specific_Logs_Length));
	printf("**** Controller Data ****\n");
	printf("Controller_GUID      ");
	print_guid(meta->cdr->Controller_GUID);
	printf("\n");
	printf("Controller_Type      0x%04x%04x 0x%04x%04x\n",
	    GET16(meta, cdr->Controller_Type.Vendor_ID),
	    GET16(meta, cdr->Controller_Type.Device_ID),
	    GET16(meta, cdr->Controller_Type.SubVendor_ID),
	    GET16(meta, cdr->Controller_Type.SubDevice_ID));
	printf("Product_ID           '%.16s'\n", (char *)&meta->cdr->Product_ID[0]);
	printf("**** Physical Disk Records ****\n");
	printf("Populated_PDEs       %u\n", GET16(meta, pdr->Populated_PDEs));
	printf("Max_PDE_Supported    %u\n", GET16(meta, pdr->Max_PDE_Supported));
	for (j = 0; j < GET16(meta, pdr->Populated_PDEs); j++) {
		if (isff(meta->pdr->entry[j].PD_GUID, 24))
			continue;
		if (GET32(meta, pdr->entry[j].PD_Reference) == 0xffffffff)
			continue;
		printf("PD_GUID              ");
		print_guid(meta->pdr->entry[j].PD_GUID);
		printf("\n");
		printf("PD_Reference         0x%08x\n",
		    GET32(meta, pdr->entry[j].PD_Reference));
		printf("PD_Type              0x%04x\n",
		    GET16(meta, pdr->entry[j].PD_Type));
		printf("PD_State             0x%04x\n",
		    GET16(meta, pdr->entry[j].PD_State));
		printf("Configured_Size      %ju\n",
		    GET64(meta, pdr->entry[j].Configured_Size));
		printf("Block_Size           %u\n",
		    GET16(meta, pdr->entry[j].Block_Size));
	}
	printf("**** Virtual Disk Records ****\n");
	printf("Populated_VDEs       %u\n", GET16(meta, vdr->Populated_VDEs));
	printf("Max_VDE_Supported    %u\n", GET16(meta, vdr->Max_VDE_Supported));
	for (j = 0; j < GET16(meta, vdr->Populated_VDEs); j++) {
		if (isff(meta->vdr->entry[j].VD_GUID, 24))
			continue;
		printf("VD_GUID              ");
		print_guid(meta->vdr->entry[j].VD_GUID);
		printf("\n");
		printf("VD_Number            0x%04x\n",
		    GET16(meta, vdr->entry[j].VD_Number));
		printf("VD_Type              0x%04x\n",
		    GET16(meta, vdr->entry[j].VD_Type));
		printf("VD_State             0x%02x\n",
		    GET8(meta, vdr->entry[j].VD_State));
		printf("Init_State           0x%02x\n",
		    GET8(meta, vdr->entry[j].Init_State));
		printf("Drive_Failures_Remaining %u\n",
		    GET8(meta, vdr->entry[j].Drive_Failures_Remaining));
		printf("VD_Name              '%.16s'\n",
		    (char *)&meta->vdr->entry[j].VD_Name);
	}
	printf("**** Configuration Records ****\n");
	num = GETCRNUM(meta);
	for (j = 0; j < num; j++) {
		vdc = GETVDCPTR(meta, j);
		val = GET32D(meta, vdc->Signature);
		switch (val) {
		case DDF_VDCR_SIGNATURE:
			printf("** Virtual Disk Configuration **\n");
			printf("VD_GUID              ");
			print_guid(vdc->VD_GUID);
			printf("\n");
			printf("Timestamp            0x%08x\n",
			    GET32D(meta, vdc->Timestamp));
			printf("Sequence_Number      0x%08x\n",
			    GET32D(meta, vdc->Sequence_Number));
			printf("Primary_Element_Count %u\n",
			    GET16D(meta, vdc->Primary_Element_Count));
			printf("Stripe_Size          %u\n",
			    GET8D(meta, vdc->Stripe_Size));
			printf("Primary_RAID_Level   0x%02x\n",
			    GET8D(meta, vdc->Primary_RAID_Level));
			printf("RLQ                  0x%02x\n",
			    GET8D(meta, vdc->RLQ));
			printf("Secondary_Element_Count %u\n",
			    GET8D(meta, vdc->Secondary_Element_Count));
			printf("Secondary_Element_Seq %u\n",
			    GET8D(meta, vdc->Secondary_Element_Seq));
			printf("Secondary_RAID_Level 0x%02x\n",
			    GET8D(meta, vdc->Secondary_RAID_Level));
			printf("Block_Count          %ju\n",
			    GET64D(meta, vdc->Block_Count));
			printf("VD_Size              %ju\n",
			    GET64D(meta, vdc->VD_Size));
			printf("Block_Size           %u\n",
			    GET16D(meta, vdc->Block_Size));
			printf("Rotate_Parity_count  %u\n",
			    GET8D(meta, vdc->Rotate_Parity_count));
			printf("Associated_Spare_Disks");
			for (i = 0; i < 8; i++) {
				if (GET32D(meta, vdc->Associated_Spares[i]) != 0xffffffff)
					printf(" 0x%08x", GET32D(meta, vdc->Associated_Spares[i]));
			}
			printf("\n");
			printf("Cache_Flags          %016jx\n",
			    GET64D(meta, vdc->Cache_Flags));
			printf("BG_Rate              %u\n",
			    GET8D(meta, vdc->BG_Rate));
			printf("MDF_Parity_Disks     %u\n",
			    GET8D(meta, vdc->MDF_Parity_Disks));
			printf("MDF_Parity_Generator_Polynomial 0x%04x\n",
			    GET16D(meta, vdc->MDF_Parity_Generator_Polynomial));
			printf("MDF_Constant_Generation_Method 0x%02x\n",
			    GET8D(meta, vdc->MDF_Constant_Generation_Method));
			printf("Physical_Disks      ");
			num2 = GET16D(meta, vdc->Primary_Element_Count);
			val2 = (uint64_t *)&(vdc->Physical_Disk_Sequence[GET16(meta, hdr->Max_Primary_Element_Entries)]);
			for (i = 0; i < num2; i++)
				printf(" 0x%08x @ %ju",
				    GET32D(meta, vdc->Physical_Disk_Sequence[i]),
				    GET64P(meta, val2 + i));
			printf("\n");
			break;
		case DDF_VUCR_SIGNATURE:
			printf("** Vendor Unique Configuration **\n");
			vuc = (struct ddf_vuc_record *)vdc;
			printf("VD_GUID              ");
			print_guid(vuc->VD_GUID);
			printf("\n");
			break;
		case DDF_SA_SIGNATURE:
			printf("** Spare Assignment Configuration **\n");
			sa = (struct ddf_sa_record *)vdc;
			printf("Timestamp            0x%08x\n",
			    GET32D(meta, sa->Timestamp));
			printf("Spare_Type           0x%02x\n",
			    GET8D(meta, sa->Spare_Type));
			printf("Populated_SAEs       %u\n",
			    GET16D(meta, sa->Populated_SAEs));
			printf("MAX_SAE_Supported    %u\n",
			    GET16D(meta, sa->MAX_SAE_Supported));
			for (i = 0; i < GET16D(meta, sa->Populated_SAEs); i++) {
				if (isff(sa->entry[i].VD_GUID, 24))
					continue;
				printf("VD_GUID             ");
				for (k = 0; k < 24; k++)
					printf("%02x", sa->entry[i].VD_GUID[k]);
				printf("\n");
				printf("Secondary_Element   %u\n",
				    GET16D(meta, sa->entry[i].Secondary_Element));
			}
			break;
		case 0x00000000:
		case 0xFFFFFFFF:
			break;
		default:
			printf("Unknown configuration signature %08x\n", val);
			break;
		}
	}
	printf("**** Physical Disk Data ****\n");
	printf("PD_GUID              ");
	print_guid(meta->pdd->PD_GUID);
	printf("\n");
	printf("PD_Reference         0x%08x\n",
	    GET32(meta, pdd->PD_Reference));
	printf("Forced_Ref_Flag      0x%02x\n",
	    GET8(meta, pdd->Forced_Ref_Flag));
	printf("Forced_PD_GUID_Flag  0x%02x\n",
	    GET8(meta, pdd->Forced_PD_GUID_Flag));
}