#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_data {int dummy; } ;
struct TYPE_6__ {struct scsi_sense_data* sense_buffers; } ;
struct TYPE_5__ {int TagNumber; } ;
typedef  TYPE_1__* PSRB ;
typedef  TYPE_2__* PACB ;

/* Variables and functions */

__attribute__((used)) static struct scsi_sense_data *
trm_get_sense_buf(PACB pACB, PSRB pSRB)
{
	int offset;

	offset = pSRB->TagNumber;
	return (&pACB->sense_buffers[offset]);
}