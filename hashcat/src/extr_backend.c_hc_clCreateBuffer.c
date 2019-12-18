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
struct TYPE_6__ {TYPE_2__* backend_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
typedef  int /*<<< orphan*/  cl_mem_flags ;
typedef  int /*<<< orphan*/  cl_mem ;
typedef  scalar_t__ cl_int ;
typedef  int /*<<< orphan*/  cl_context ;
struct TYPE_7__ {scalar_t__ ocl; } ;
typedef  TYPE_2__ backend_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* clCreateBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*,scalar_t__*) ;} ;
typedef  TYPE_3__ OCL_PTR ;

/* Variables and functions */
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  event_log_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*,scalar_t__*) ; 
 int /*<<< orphan*/  val2cstr_cl (scalar_t__) ; 

int hc_clCreateBuffer (hashcat_ctx_t *hashcat_ctx, cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_mem *mem)
{
  backend_ctx_t *backend_ctx = hashcat_ctx->backend_ctx;

  OCL_PTR *ocl = (OCL_PTR *) backend_ctx->ocl;

  cl_int CL_err;

  *mem = ocl->clCreateBuffer (context, flags, size, host_ptr, &CL_err);

  if (CL_err != CL_SUCCESS)
  {
    event_log_error (hashcat_ctx, "clCreateBuffer(): %s", val2cstr_cl (CL_err));

    return -1;
  }

  return 0;
}