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
struct scsi_static_inquiry_pattern {int /*<<< orphan*/  revision; int /*<<< orphan*/  product; } ;
struct ata_params {int /*<<< orphan*/  revision; int /*<<< orphan*/  model; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ cam_strmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
ata_static_identify_match(caddr_t identbuffer, caddr_t table_entry)
{
	struct scsi_static_inquiry_pattern *entry;
	struct ata_params *ident;
 
	entry = (struct scsi_static_inquiry_pattern *)table_entry;
	ident = (struct ata_params *)identbuffer;

	if ((cam_strmatch(ident->model, entry->product,
			  sizeof(ident->model)) == 0)
	 && (cam_strmatch(ident->revision, entry->revision,
			  sizeof(ident->revision)) == 0)) {
		return (0);
	}
        return (-1);
}