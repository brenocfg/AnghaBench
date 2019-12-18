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
struct scsi_sense_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_extract_sense_len (struct scsi_sense_data*,int,int*,int*,int*,int*,int /*<<< orphan*/ ) ; 

void
scsi_extract_sense(struct scsi_sense_data *sense_data, int *error_code,
		   int *sense_key, int *asc, int *ascq)
{
	scsi_extract_sense_len(sense_data, sizeof(*sense_data), error_code,
			       sense_key, asc, ascq, /*show_errors*/ 0);
}