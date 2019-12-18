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
typedef  int uint32_t ;
struct scsi_report_luns_data {TYPE_1__* luns; } ;
struct TYPE_2__ {int* lundata; } ;

/* Variables and functions */
#define  RPL_LUNDATA_ATYP_EXTLUN 131 
#define  RPL_LUNDATA_ATYP_FLAT 130 
#define  RPL_LUNDATA_ATYP_LUN 129 
 int RPL_LUNDATA_ATYP_MASK ; 
#define  RPL_LUNDATA_ATYP_PERIPH 128 
 int RPL_LUNDATA_FLAT_LUN_BITS ; 
 int RPL_LUNDATA_FLAT_LUN_MASK ; 
 int cctl_get_luns (int,int,int,int,struct scsi_report_luns_data**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct scsi_report_luns_data*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
cctl_report_luns(int fd, int lun, int iid, int retries)
{
	struct scsi_report_luns_data *lun_data;
	uint32_t num_luns, i;
	int retval;

	lun_data = NULL;

	if ((retval = cctl_get_luns(fd, lun, iid, retries, &lun_data,
				   &num_luns)) != 0)
		goto bailout;

	fprintf(stdout, "%u LUNs returned\n", num_luns);
	for (i = 0; i < num_luns; i++) {
		int lun_val;

		/*
		 * XXX KDM figure out a way to share this code with
		 * cctl_lunlist()?
		 */
		switch (lun_data->luns[i].lundata[0] & RPL_LUNDATA_ATYP_MASK) {
		case RPL_LUNDATA_ATYP_PERIPH:
			lun_val = lun_data->luns[i].lundata[1];
			break;
		case RPL_LUNDATA_ATYP_FLAT:
			lun_val = (lun_data->luns[i].lundata[0] &
				RPL_LUNDATA_FLAT_LUN_MASK) |
				(lun_data->luns[i].lundata[1] <<
				RPL_LUNDATA_FLAT_LUN_BITS);
			break;
		case RPL_LUNDATA_ATYP_LUN:
		case RPL_LUNDATA_ATYP_EXTLUN:
		default:
			fprintf(stdout, "Unsupported LUN format %d\n",
				lun_data->luns[i].lundata[0] &
				RPL_LUNDATA_ATYP_MASK);
			lun_val = -1;
			break;
		}
		if (lun_val == -1)
			continue;

		fprintf(stdout, "%d\n", lun_val);
	}

bailout:
	if (lun_data != NULL)
		free(lun_data);

	return (retval);
}