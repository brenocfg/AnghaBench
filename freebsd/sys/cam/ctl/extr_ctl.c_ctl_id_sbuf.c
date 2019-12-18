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
struct scsi_vpd_id_descriptor {int id_type; int proto_codeset; int length; char** identifier; } ;
struct sbuf {int dummy; } ;
struct ctl_devid {int len; scalar_t__ data; } ;

/* Variables and functions */
#define  SVPD_ID_CODESET_ASCII 134 
#define  SVPD_ID_CODESET_BINARY 133 
 int SVPD_ID_CODESET_MASK ; 
#define  SVPD_ID_CODESET_UTF8 132 
#define  SVPD_ID_TYPE_EUI64 131 
 int SVPD_ID_TYPE_MASK ; 
#define  SVPD_ID_TYPE_NAA 130 
#define  SVPD_ID_TYPE_SCSI_NAME 129 
#define  SVPD_ID_TYPE_T10 128 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
ctl_id_sbuf(struct ctl_devid *id, struct sbuf *sb)
{
	struct scsi_vpd_id_descriptor *desc;
	int i;

	if (id == NULL || id->len < 4)
		return;
	desc = (struct scsi_vpd_id_descriptor *)id->data;
	switch (desc->id_type & SVPD_ID_TYPE_MASK) {
	case SVPD_ID_TYPE_T10:
		sbuf_printf(sb, "t10.");
		break;
	case SVPD_ID_TYPE_EUI64:
		sbuf_printf(sb, "eui.");
		break;
	case SVPD_ID_TYPE_NAA:
		sbuf_printf(sb, "naa.");
		break;
	case SVPD_ID_TYPE_SCSI_NAME:
		break;
	}
	switch (desc->proto_codeset & SVPD_ID_CODESET_MASK) {
	case SVPD_ID_CODESET_BINARY:
		for (i = 0; i < desc->length; i++)
			sbuf_printf(sb, "%02x", desc->identifier[i]);
		break;
	case SVPD_ID_CODESET_ASCII:
		sbuf_printf(sb, "%.*s", (int)desc->length,
		    (char *)desc->identifier);
		break;
	case SVPD_ID_CODESET_UTF8:
		sbuf_printf(sb, "%s", (char *)desc->identifier);
		break;
	}
}