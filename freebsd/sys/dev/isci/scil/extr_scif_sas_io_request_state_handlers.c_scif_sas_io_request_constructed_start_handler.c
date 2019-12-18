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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_SUCCESS ; 

SCI_STATUS scif_sas_io_request_constructed_start_handler(
   SCI_BASE_REQUEST_T * io_request
)
{
   return SCI_SUCCESS;
}