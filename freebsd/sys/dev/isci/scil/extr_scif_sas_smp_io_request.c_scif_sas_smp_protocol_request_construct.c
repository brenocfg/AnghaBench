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
typedef  void* U8 ;
struct TYPE_4__ {void* request_length; void* allocated_response_length; void* function; int /*<<< orphan*/  smp_frame_type; } ;
struct TYPE_5__ {TYPE_1__ header; } ;
typedef  TYPE_2__ SMP_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_FRAME_TYPE_REQUEST ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void scif_sas_smp_protocol_request_construct(
   SMP_REQUEST_T * smp_request,
   U8              smp_function,
   U8              smp_response_length,
   U8              smp_request_length
)
{
   memset((char*)smp_request, 0, sizeof(SMP_REQUEST_T));

   smp_request->header.smp_frame_type            = SMP_FRAME_TYPE_REQUEST;
   smp_request->header.function                  = smp_function;
   smp_request->header.allocated_response_length = smp_response_length;
   smp_request->header.request_length            = smp_request_length;
}