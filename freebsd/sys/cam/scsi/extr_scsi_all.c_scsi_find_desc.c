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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_data_desc {int dummy; } ;
struct scsi_find_desc_info {int /*<<< orphan*/ * header; int /*<<< orphan*/  desc_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_desc_iterate (struct scsi_sense_data_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_find_desc_info*) ; 
 int /*<<< orphan*/  scsi_find_desc_func ; 

uint8_t *
scsi_find_desc(struct scsi_sense_data_desc *sense, u_int sense_len,
	       uint8_t desc_type)
{
	struct scsi_find_desc_info desc_info;

	desc_info.desc_type = desc_type;
	desc_info.header = NULL;

	scsi_desc_iterate(sense, sense_len, scsi_find_desc_func, &desc_info);

	return ((uint8_t *)desc_info.header);
}