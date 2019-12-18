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
struct scsi_sense_hdr {int /*<<< orphan*/  sense_key; int /*<<< orphan*/  ascq; int /*<<< orphan*/  asc; } ;
struct pktcdvd_device {int dummy; } ;
struct packet_command {int /*<<< orphan*/  cmd; struct scsi_sense_hdr* sshdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDROM_PACKET_SIZE ; 
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sense_key_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pkt_dump_sense(struct pktcdvd_device *pd,
			   struct packet_command *cgc)
{
	struct scsi_sense_hdr *sshdr = cgc->sshdr;

	if (sshdr)
		pkt_err(pd, "%*ph - sense %02x.%02x.%02x (%s)\n",
			CDROM_PACKET_SIZE, cgc->cmd,
			sshdr->sense_key, sshdr->asc, sshdr->ascq,
			sense_key_string(sshdr->sense_key));
	else
		pkt_err(pd, "%*ph - no sense\n", CDROM_PACKET_SIZE, cgc->cmd);
}