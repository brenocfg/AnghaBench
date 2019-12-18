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
struct sbuf {int dummy; } ;
struct ata_params {int config; int satacapabilities; int /*<<< orphan*/  version_major; } ;

/* Variables and functions */
 int ATA_PROTO_ATAPI ; 
 int ATA_PROTO_CFA ; 
 int ATA_SATA_GEN1 ; 
 int ATA_SATA_GEN2 ; 
 int ATA_SATA_GEN3 ; 
 int /*<<< orphan*/  ata_print_ident_short_sbuf (struct ata_params*,struct sbuf*) ; 
 int ata_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

void
ata_print_ident_sbuf(struct ata_params *ident_data, struct sbuf *sb)
{
	const char *proto, *sata;
	int version;

	ata_print_ident_short_sbuf(ident_data, sb);
	sbuf_printf(sb, " ");

	proto = (ident_data->config == ATA_PROTO_CFA) ? "CFA" :
		(ident_data->config & ATA_PROTO_ATAPI) ? "ATAPI" : "ATA";
	version = ata_version(ident_data->version_major);

	switch (version) {
	case 0:
		sbuf_printf(sb, "%s", proto);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		sbuf_printf(sb, "%s-%d", proto, version);
		break;
	case 8:
		sbuf_printf(sb, "%s8-ACS", proto);
		break;
	default:
		sbuf_printf(sb, "ACS-%d %s", version - 7, proto);
		break;
	}

	if (ident_data->satacapabilities && ident_data->satacapabilities != 0xffff) {
		if (ident_data->satacapabilities & ATA_SATA_GEN3)
			sata = " SATA 3.x";
		else if (ident_data->satacapabilities & ATA_SATA_GEN2)
			sata = " SATA 2.x";
		else if (ident_data->satacapabilities & ATA_SATA_GEN1)
			sata = " SATA 1.x";
		else
			sata = " SATA";
	} else
		sata = "";
	sbuf_printf(sb, "%s device\n", sata);
}