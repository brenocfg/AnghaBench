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
typedef  int /*<<< orphan*/  cl_program ;
typedef  int /*<<< orphan*/  cl_kernel ;
typedef  scalar_t__ cl_int ;
struct TYPE_8__ {int /*<<< orphan*/  (* clCreateKernel ) (int /*<<< orphan*/ ,char const*,scalar_t__*) ;} ;
typedef  TYPE_3__ OCL_PTR ;

/* Variables and functions */
 scalar_t__ CL_SUCCESS ; 
 int /*<<< orphan*/  event_log_error (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  val2cstr_cl (scalar_t__) ; 

int hc_clCreateKernel (hashcat_ctx_t *hashcat_ctx, cl_program program, const char *kernel_name, cl_kernel *kernel)
{
  opencl_ctx_t *opencl_ctx = hashcat_ctx->opencl_ctx;

  OCL_PTR *ocl = opencl_ctx->ocl;

  cl_int CL_err;

  *kernel = ocl->clCreateKernel (program, kernel_name, &CL_err);

  if (CL_err != CL_SUCCESS)
  {
    event_log_error (hashcat_ctx, "clCreateKernel(): %s", val2cstr_cl (CL_err));

    return -1;
  }

  return 0;
}