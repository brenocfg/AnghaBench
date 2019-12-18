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
struct sbuf {int dummy; } ;
struct TYPE_2__ {int status; int error; } ;
struct ccb_ataio {TYPE_1__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,char*,char*,char*,char*,char*,char*,char*,char*) ; 

int
ata_status_sbuf(struct ccb_ataio *ataio, struct sbuf *sb)
{

	sbuf_printf(sb, "ATA status: %02x (%s%s%s%s%s%s%s%s)",
	    ataio->res.status,
	    (ataio->res.status & 0x80) ? "BSY " : "",
	    (ataio->res.status & 0x40) ? "DRDY " : "",
	    (ataio->res.status & 0x20) ? "DF " : "",
	    (ataio->res.status & 0x10) ? "SERV " : "",
	    (ataio->res.status & 0x08) ? "DRQ " : "",
	    (ataio->res.status & 0x04) ? "CORR " : "",
	    (ataio->res.status & 0x02) ? "IDX " : "",
	    (ataio->res.status & 0x01) ? "ERR" : "");
	if (ataio->res.status & 1) {
	    sbuf_printf(sb, ", error: %02x (%s%s%s%s%s%s%s%s)",
		ataio->res.error,
		(ataio->res.error & 0x80) ? "ICRC " : "",
		(ataio->res.error & 0x40) ? "UNC " : "",
		(ataio->res.error & 0x20) ? "MC " : "",
		(ataio->res.error & 0x10) ? "IDNF " : "",
		(ataio->res.error & 0x08) ? "MCR " : "",
		(ataio->res.error & 0x04) ? "ABRT " : "",
		(ataio->res.error & 0x02) ? "NM " : "",
		(ataio->res.error & 0x01) ? "ILI" : "");
	}

	return(0);
}