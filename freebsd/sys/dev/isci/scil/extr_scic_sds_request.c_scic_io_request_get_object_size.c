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
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_smp_request_get_object_size () ; 
 int /*<<< orphan*/  scic_sds_ssp_request_get_object_size () ; 
 int /*<<< orphan*/  scic_sds_stp_request_get_object_size () ; 

U32 scic_io_request_get_object_size(void)
{
   U32 ssp_request_size;
   U32 stp_request_size;
   U32 smp_request_size;

   ssp_request_size = scic_sds_ssp_request_get_object_size();
   stp_request_size = scic_sds_stp_request_get_object_size();
   smp_request_size = scic_sds_smp_request_get_object_size();

   return MAX(ssp_request_size, MAX(stp_request_size, smp_request_size));
}