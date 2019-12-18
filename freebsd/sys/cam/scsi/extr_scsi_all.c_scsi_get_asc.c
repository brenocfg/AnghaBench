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
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_extract_sense_len (struct scsi_sense_data*,int /*<<< orphan*/ ,int*,int*,int*,int*,int) ; 

int
scsi_get_asc(struct scsi_sense_data *sense_data, u_int sense_len,
	     int show_errors)
{
	int error_code, sense_key, asc, ascq;

	scsi_extract_sense_len(sense_data, sense_len, &error_code,
			       &sense_key, &asc, &ascq, show_errors);

	return (asc);
}