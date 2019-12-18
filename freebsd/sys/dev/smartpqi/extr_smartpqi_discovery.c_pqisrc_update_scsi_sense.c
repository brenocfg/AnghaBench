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
struct sense_header_scsi {int response_code; int sense_key; int asc; int ascq; int additional_length; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  memset (struct sense_header_scsi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pqisrc_scsi_sense_valid (struct sense_header_scsi*) ; 

boolean_t pqisrc_update_scsi_sense(const uint8_t *buff, int len,
			      struct sense_header_scsi *header)
{

	DBG_FUNC("IN\n");

	if (!buff || !len)
		return false;

	memset(header, 0, sizeof(struct sense_header_scsi));

	header->response_code = (buff[0] & 0x7f);

	if (!pqisrc_scsi_sense_valid(header))
		return false;

	if (header->response_code >= 0x72) {
		/* descriptor format */
		if (len > 1)
			header->sense_key = (buff[1] & 0xf);
		if (len > 2)
			header->asc = buff[2];
		if (len > 3)
			header->ascq = buff[3];
		if (len > 7)
			header->additional_length = buff[7];
	} else {
		 /* fixed format */
		if (len > 2)
			header->sense_key = (buff[2] & 0xf);
		if (len > 7) {
			len = (len < (buff[7] + 8)) ?
					len : (buff[7] + 8);
			if (len > 12)
				header->asc = buff[12];
			if (len > 13)
				header->ascq = buff[13];
		}
	}

	DBG_FUNC("OUT\n");

	return true;
}