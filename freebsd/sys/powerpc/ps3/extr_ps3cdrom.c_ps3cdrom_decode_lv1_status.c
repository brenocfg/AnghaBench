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
typedef  int uint64_t ;
typedef  int u_int8_t ;

/* Variables and functions */
 int SCSI_STATUS_CHECK_COND ; 

__attribute__((used)) static int
ps3cdrom_decode_lv1_status(uint64_t status, u_int8_t *sense_key, u_int8_t *asc,
    u_int8_t *ascq)
{
	if (((status >> 24) & 0xff) != SCSI_STATUS_CHECK_COND)
		return -1;

	*sense_key = (status >> 16) & 0xff;
	*asc = (status >> 8) & 0xff;
	*ascq = status & 0xff;

	return (0);
}