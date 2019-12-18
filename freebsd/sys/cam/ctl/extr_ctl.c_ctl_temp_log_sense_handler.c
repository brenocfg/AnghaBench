#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int param_len; void* param_control; int /*<<< orphan*/  param_code; } ;
struct scsi_log_temperature {int temperature; TYPE_1__ hdr; } ;
struct scsi_log_param_header {int dummy; } ;
struct ctl_scsiio {int dummy; } ;
struct ctl_page_index {scalar_t__ page_data; } ;
struct ctl_lun {TYPE_2__* be_lun; } ;
struct TYPE_4__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 struct ctl_lun* CTL_LUN (struct ctl_scsiio*) ; 
 void* SLP_LBIN ; 
 int /*<<< orphan*/  SLP_REFTEMPERATURE ; 
 int /*<<< orphan*/  SLP_TEMPERATURE ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ctl_temp_log_sense_handler(struct ctl_scsiio *ctsio,
			       struct ctl_page_index *page_index,
			       int pc)
{
	struct ctl_lun *lun = CTL_LUN(ctsio);
	struct scsi_log_temperature *data;
	const char *value;

	data = (struct scsi_log_temperature *)page_index->page_data;

	scsi_ulto2b(SLP_TEMPERATURE, data->hdr.param_code);
	data->hdr.param_control = SLP_LBIN;
	data->hdr.param_len = sizeof(struct scsi_log_temperature) -
	    sizeof(struct scsi_log_param_header);
	if ((value = dnvlist_get_string(lun->be_lun->options, "temperature",
	    NULL)) != NULL)
		data->temperature = strtol(value, NULL, 0);
	else
		data->temperature = 0xff;
	data++;

	scsi_ulto2b(SLP_REFTEMPERATURE, data->hdr.param_code);
	data->hdr.param_control = SLP_LBIN;
	data->hdr.param_len = sizeof(struct scsi_log_temperature) -
	    sizeof(struct scsi_log_param_header);
	if ((value = dnvlist_get_string(lun->be_lun->options, "reftemperature",
	    NULL)) != NULL)
		data->temperature = strtol(value, NULL, 0);
	else
		data->temperature = 0xff;
	return (0);
}