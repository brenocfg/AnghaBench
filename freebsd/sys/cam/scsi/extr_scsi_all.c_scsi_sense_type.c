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
struct scsi_sense_data {int error_code; } ;
typedef  int /*<<< orphan*/  scsi_sense_data_type ;

/* Variables and functions */
#define  SSD_CURRENT_ERROR 131 
#define  SSD_DEFERRED_ERROR 130 
#define  SSD_DESC_CURRENT_ERROR 129 
#define  SSD_DESC_DEFERRED_ERROR 128 
 int SSD_ERRCODE ; 
 int /*<<< orphan*/  SSD_TYPE_DESC ; 
 int /*<<< orphan*/  SSD_TYPE_FIXED ; 
 int /*<<< orphan*/  SSD_TYPE_NONE ; 

scsi_sense_data_type
scsi_sense_type(struct scsi_sense_data *sense_data)
{
	switch (sense_data->error_code & SSD_ERRCODE) {
	case SSD_DESC_CURRENT_ERROR:
	case SSD_DESC_DEFERRED_ERROR:
		return (SSD_TYPE_DESC);
		break;
	case SSD_CURRENT_ERROR:
	case SSD_DEFERRED_ERROR:
		return (SSD_TYPE_FIXED);
		break;
	default:
		break;
	}

	return (SSD_TYPE_NONE);
}