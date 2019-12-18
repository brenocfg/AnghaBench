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
typedef  union ctl_io {int dummy; } ctl_io ;
typedef  int uint8_t ;
struct ctl_scsiio {int* cdb; } ;
struct ctl_cmd_entry {int length; int* usage; int /*<<< orphan*/ * execute; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 struct ctl_cmd_entry* ctl_get_cmd_entry (struct ctl_scsiio*,int*) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int,int) ; 
 int /*<<< orphan*/  ctl_set_invalid_opcode (struct ctl_scsiio*) ; 
 int fls (int) ; 

const struct ctl_cmd_entry *
ctl_validate_command(struct ctl_scsiio *ctsio)
{
	const struct ctl_cmd_entry *entry;
	int i, sa;
	uint8_t diff;

	entry = ctl_get_cmd_entry(ctsio, &sa);
	if (entry->execute == NULL) {
		if (sa)
			ctl_set_invalid_field(ctsio,
					      /*sks_valid*/ 1,
					      /*command*/ 1,
					      /*field*/ 1,
					      /*bit_valid*/ 1,
					      /*bit*/ 4);
		else
			ctl_set_invalid_opcode(ctsio);
		ctl_done((union ctl_io *)ctsio);
		return (NULL);
	}
	KASSERT(entry->length > 0,
	    ("Not defined length for command 0x%02x/0x%02x",
	     ctsio->cdb[0], ctsio->cdb[1]));
	for (i = 1; i < entry->length; i++) {
		diff = ctsio->cdb[i] & ~entry->usage[i - 1];
		if (diff == 0)
			continue;
		ctl_set_invalid_field(ctsio,
				      /*sks_valid*/ 1,
				      /*command*/ 1,
				      /*field*/ i,
				      /*bit_valid*/ 1,
				      /*bit*/ fls(diff) - 1);
		ctl_done((union ctl_io *)ctsio);
		return (NULL);
	}
	return (entry);
}