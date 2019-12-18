#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int is_cuda; scalar_t__ is_opencl; scalar_t__ device_processors; scalar_t__ device_maxclock_frequency; scalar_t__ device_maxworkgroup_size; scalar_t__ sm_major; scalar_t__ sm_minor; scalar_t__ kernel_exec_timeout; int /*<<< orphan*/  opencl_driver_version; int /*<<< orphan*/  opencl_device_version; int /*<<< orphan*/  opencl_device_vendor; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ hc_device_param_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_same_device_type (const hc_device_param_t *src, const hc_device_param_t *dst)
{
  if (strcmp (src->device_name, dst->device_name) != 0) return false;

  if (src->is_cuda   != dst->is_cuda)   return false;
  if (src->is_opencl != dst->is_opencl) return false;

  if (src->is_cuda == true)
  {
    if (strcmp (src->opencl_device_vendor,  dst->opencl_device_vendor)  != 0) return false;
    if (strcmp (src->opencl_device_version, dst->opencl_device_version) != 0) return false;
    if (strcmp (src->opencl_driver_version, dst->opencl_driver_version) != 0) return false;
  }

  if (src->device_processors         != dst->device_processors)         return false;
  if (src->device_maxclock_frequency != dst->device_maxclock_frequency) return false;
  if (src->device_maxworkgroup_size  != dst->device_maxworkgroup_size)  return false;

  // memory size can be different, depending on which gpu has a monitor connected
  // if (src->device_maxmem_alloc       != dst->device_maxmem_alloc)       return false;
  // if (src->device_global_mem         != dst->device_global_mem)         return false;

  if (src->sm_major != dst->sm_major) return false;
  if (src->sm_minor != dst->sm_minor) return false;

  if (src->kernel_exec_timeout != dst->kernel_exec_timeout) return false;

  return true;
}