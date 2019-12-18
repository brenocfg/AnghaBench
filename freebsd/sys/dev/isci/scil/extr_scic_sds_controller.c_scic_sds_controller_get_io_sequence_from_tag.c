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
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sds_io_tag_get_sequence (int /*<<< orphan*/ ) ; 

U16 scic_sds_controller_get_io_sequence_from_tag(
   SCIC_SDS_CONTROLLER_T *this_controller,
   U16                    io_tag
)
{
   return scic_sds_io_tag_get_sequence(io_tag);
}