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
typedef  int U8 ;
typedef  int U32 ;
struct TYPE_4__ {int medium_type; } ;
struct TYPE_3__ {int medium_type; } ;
typedef  TYPE_1__ SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_6_T ;
typedef  TYPE_2__ SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_10_T ;

/* Variables and functions */

__attribute__((used)) static
U8 sati_mode_select_get_medium_type(
   U8 * mode_parameters,
   U32  cdb_size
)
{
   U8  medium_type =0xFF;
   SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_6_T * mode_parameters_6;
   SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_10_T * mode_parameters_10;

   if(cdb_size == 6)
   {
      mode_parameters_6 = (SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_6_T *) mode_parameters;
      medium_type = mode_parameters_6->medium_type;
   }
   else if(cdb_size == 10)
   {
      mode_parameters_10 = (SCSI_MODE_SELECT_MODE_PARAMETER_HEADER_10_T *) mode_parameters;
      medium_type = mode_parameters_10->medium_type;
   }

   return medium_type;
}