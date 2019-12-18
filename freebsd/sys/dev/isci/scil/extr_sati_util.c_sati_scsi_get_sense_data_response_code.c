#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {scalar_t__ descriptor_sense_enable; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE ; 
 int /*<<< orphan*/  SCSI_FIXED_CURRENT_RESPONSE_CODE ; 

__attribute__((used)) static
U8 sati_scsi_get_sense_data_response_code(SATI_TRANSLATOR_SEQUENCE_T * sequence)
{
    if (sequence->device->descriptor_sense_enable)
    {
       return SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE;
    }
    else
    {
       return SCSI_FIXED_CURRENT_RESPONSE_CODE;
    }
}