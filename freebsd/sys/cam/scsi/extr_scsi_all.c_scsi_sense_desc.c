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
struct sense_key_table_entry {char* desc; } ;
struct scsi_inquiry_data {int dummy; } ;
struct asc_table_entry {char* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fetchtableentries (int,int,int,struct scsi_inquiry_data*,struct sense_key_table_entry const**,struct asc_table_entry const**) ; 

void
scsi_sense_desc(int sense_key, int asc, int ascq,
		struct scsi_inquiry_data *inq_data,
		const char **sense_key_desc, const char **asc_desc)
{
	const struct asc_table_entry *asc_entry;
	const struct sense_key_table_entry *sense_entry;

	fetchtableentries(sense_key, asc, ascq,
			  inq_data,
			  &sense_entry,
			  &asc_entry);

	if (sense_entry != NULL)
		*sense_key_desc = sense_entry->desc;
	else
		*sense_key_desc = "Invalid Sense Key";

	if (asc_entry != NULL)
		*asc_desc = asc_entry->desc;
	else if (asc >= 0x80 && asc <= 0xff)
		*asc_desc = "Vendor Specific ASC";
	else if (ascq >= 0x80 && ascq <= 0xff)
		*asc_desc = "Vendor Specific ASCQ";
	else
		*asc_desc = "Reserved ASC/ASCQ pair";
}