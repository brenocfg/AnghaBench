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
typedef  int u32 ;
struct TYPE_6__ {int kernel_threads_min; int kernel_threads_max; int device_type; int kernel_preferred_wgs_multiple1; int kernel_preferred_wgs_multiple4; int kernel_preferred_wgs_multiple2; int /*<<< orphan*/  device_maxworkgroup_size; } ;
typedef  TYPE_1__ hc_device_param_t ;
struct TYPE_7__ {int opts_type; scalar_t__ attack_exec; int opti_type; } ;
typedef  TYPE_2__ hashconfig_t ;
struct TYPE_8__ {TYPE_2__* hashconfig; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ ATTACK_EXEC_INSIDE_KERNEL ; 
 int CL_DEVICE_TYPE_CPU ; 
 int OPTI_TYPE_OPTIMIZED_KERNEL ; 
 int OPTS_TYPE_PREFERED_THREAD ; 

__attribute__((used)) static u32 get_kernel_threads (hashcat_ctx_t *hashcat_ctx, const hc_device_param_t *device_param)
{
  const hashconfig_t *hashconfig = hashcat_ctx->hashconfig;

  // a module can force a fixed value

  u32 kernel_threads_min = device_param->kernel_threads_min;
  u32 kernel_threads_max = device_param->kernel_threads_max;

  // for CPU we just do 1 ...

  if (device_param->device_type & CL_DEVICE_TYPE_CPU)
  {
    if ((1 >= kernel_threads_min) && (1 <= kernel_threads_max))
    {
      kernel_threads_min = 1;
      kernel_threads_max = 1;
    }
  }

  // this is an upper limit, a good start, since our strategy is to reduce thread counts only

  const u32 device_maxworkgroup_size = (u32) device_param->device_maxworkgroup_size;

  if (device_maxworkgroup_size < kernel_threads_max)
  {
    kernel_threads_max = device_maxworkgroup_size;
  }

  u32 kernel_threads = kernel_threads_max;

  // complicated kernel tend to confuse OpenCL runtime suggestions for maximum thread size
  // let's workaround that by sticking to their device specific preferred thread size

  if (hashconfig->opts_type & OPTS_TYPE_PREFERED_THREAD)
  {
    if (hashconfig->attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
    {
      if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
      {
        if (device_param->kernel_preferred_wgs_multiple1)
        {
          const u32 kernel_preferred_wgs_multiple1 = device_param->kernel_preferred_wgs_multiple1;

          if ((kernel_preferred_wgs_multiple1 >= kernel_threads_min) && (kernel_preferred_wgs_multiple1 <= kernel_threads_max))
          {
            kernel_threads = kernel_preferred_wgs_multiple1;
          }
        }
      }
      else
      {
        if (device_param->kernel_preferred_wgs_multiple4)
        {
          const u32 kernel_preferred_wgs_multiple4 = device_param->kernel_preferred_wgs_multiple4;

          if ((kernel_preferred_wgs_multiple4 >= kernel_threads_min) && (kernel_preferred_wgs_multiple4 <= kernel_threads_max))
          {
            kernel_threads = kernel_preferred_wgs_multiple4;
          }
        }
      }
    }
    else
    {
      if (device_param->kernel_preferred_wgs_multiple2)
      {
        const u32 kernel_preferred_wgs_multiple2 = device_param->kernel_preferred_wgs_multiple2;

        if ((kernel_preferred_wgs_multiple2 >= kernel_threads_min) && (kernel_preferred_wgs_multiple2 <= kernel_threads_max))
        {
          kernel_threads = kernel_preferred_wgs_multiple2;
        }
      }
    }
  }
  else
  {
    if (hashconfig->attack_exec == ATTACK_EXEC_INSIDE_KERNEL)
    {
      if (hashconfig->opti_type & OPTI_TYPE_OPTIMIZED_KERNEL)
      {
        if (device_param->kernel_preferred_wgs_multiple1)
        {
          const u32 kernel_preferred_wgs_multiple1 = device_param->kernel_preferred_wgs_multiple1;

          if ((kernel_preferred_wgs_multiple1 >= kernel_threads_min) && (kernel_preferred_wgs_multiple1 <= kernel_threads_max))
          {
            kernel_threads = kernel_preferred_wgs_multiple1;
          }
        }
      }
      else
      {
        if (device_param->kernel_preferred_wgs_multiple4)
        {
          const u32 kernel_preferred_wgs_multiple4 = device_param->kernel_preferred_wgs_multiple4;

          if ((kernel_preferred_wgs_multiple4 >= kernel_threads_min) && (kernel_preferred_wgs_multiple4 <= kernel_threads_max))
          {
            kernel_threads = kernel_preferred_wgs_multiple4;
          }
        }
      }
    }
    else
    {
      if (device_param->kernel_preferred_wgs_multiple2)
      {
        const u32 kernel_preferred_wgs_multiple2 = device_param->kernel_preferred_wgs_multiple2;

        if ((kernel_preferred_wgs_multiple2 >= kernel_threads_min) && (kernel_preferred_wgs_multiple2 <= kernel_threads_max))
        {
          kernel_threads = kernel_preferred_wgs_multiple2;
        }
      }
    }
  }

  return kernel_threads;
}