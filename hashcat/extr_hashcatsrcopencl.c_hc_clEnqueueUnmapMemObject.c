#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* ocl; } ;
typedef  TYPE_1__ opencl_ctx_t ;
struct TYPE_7__ {TYPE_1__* opencl_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_uint ;
typedef  int /*<<< orphan*/  cl_mem ;
typedef  scalar_t__ cl_int ;
typedef  int /*<<< orphan*/  cl_event ;
typedef  int /*<<< orphan*/  cl_command_queue ;
struct TYPE_8__ {scalar_t__ (* clEnqueueUnmapMemObject ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ OCL_PTR ;

/* Variables and functions */
 scalar_t__ const CL_SUCCESS ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val2cstr_cl (scalar_t__ const) ; 

int hc_clEnqueueUnmapMemObject (hashcat_ctx_t *hashcat_ctx, cl_command_queue command_queue, cl_mem memobj, void *mapped_ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  OCL_PTR *ocl = opencl_ctx->ocl;

  const cl_int CL_err = ocl->clEnqueueUnmapMemObject (command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);

  if (CL_err != CL_SUCCESS)
  {
    event_log_error (hashcat_ctx, "clEnqueueUnmapMemObject(): %s", val2cstr_cl (CL_err));

    return -1;
  }

  return 0;
}