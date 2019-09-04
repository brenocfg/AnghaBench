#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int quiet; int benchmark; int machine_readable; int benchmark_all; int force; int optimized_kernel_enable; int opencl_vector_width_chgd; int kernel_accel_chgd; int kernel_loops_chgd; int kernel_threads_chgd; int workload_profile_chgd; scalar_t__ workload_profile; scalar_t__ kernel_threads; scalar_t__ kernel_loops; scalar_t__ kernel_accel; scalar_t__ opencl_vector_width; scalar_t__ opencl_platforms; scalar_t__ opencl_device_types; scalar_t__ opencl_devices; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_6__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_log_info (TYPE_2__*,char*,...) ; 

void user_options_info (hashcat_ctx_t *hashcat_ctx)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->quiet == true) return;

  if (user_options->benchmark == false) return;

  if (user_options->machine_readable == false)
  {
    event_log_info (hashcat_ctx, "Benchmark relevant options:");
    event_log_info (hashcat_ctx, "===========================");

    if (user_options->benchmark_all == true)
    {
      event_log_info (hashcat_ctx, "* --benchmark-all");
    }

    if (user_options->force == true)
    {
      event_log_info (hashcat_ctx, "* --force");
    }

    if (user_options->opencl_devices)
    {
      event_log_info (hashcat_ctx, "* --opencl-devices=%s", user_options->opencl_devices);
    }

    if (user_options->opencl_device_types)
    {
      event_log_info (hashcat_ctx, "* --opencl-device-types=%s", user_options->opencl_device_types);
    }

    if (user_options->opencl_platforms)
    {
      event_log_info (hashcat_ctx, "* --opencl-platforms=%s", user_options->opencl_platforms);
    }

    if (user_options->optimized_kernel_enable == true)
    {
      event_log_info (hashcat_ctx, "* --optimized-kernel-enable");
    }

    if (user_options->opencl_vector_width_chgd == true)
    {
      event_log_info (hashcat_ctx, "* --opencl-vector-width=%u", user_options->opencl_vector_width);
    }

    if (user_options->kernel_accel_chgd == true)
    {
      event_log_info (hashcat_ctx, "* --kernel-accel=%u", user_options->kernel_accel);
    }
    else if (user_options->kernel_loops_chgd == true)
    {
      event_log_info (hashcat_ctx, "* --kernel-loops=%u", user_options->kernel_loops);
    }
    else if (user_options->kernel_threads_chgd == true)
    {
      event_log_info (hashcat_ctx, "* --kernel-threads=%u", user_options->kernel_threads);
    }
    else
    {
      if (user_options->workload_profile_chgd == true)
      {
        event_log_info (hashcat_ctx, "* --workload-profile=%u", user_options->workload_profile);
      }
    }

    event_log_info (hashcat_ctx, NULL);
  }
  else
  {
    if (user_options->benchmark_all == true)
    {
      event_log_info (hashcat_ctx, "# option: --benchmark-all");
    }

    if (user_options->force == true)
    {
      event_log_info (hashcat_ctx, "# option: --force");
    }

    if (user_options->opencl_devices)
    {
      event_log_info (hashcat_ctx, "# option: --opencl-devices=%s", user_options->opencl_devices);
    }

    if (user_options->opencl_device_types)
    {
      event_log_info (hashcat_ctx, "# option: --opencl-device-types=%s", user_options->opencl_device_types);
    }

    if (user_options->opencl_platforms)
    {
      event_log_info (hashcat_ctx, "* option: --opencl-platforms=%s", user_options->opencl_platforms);
    }

    if (user_options->optimized_kernel_enable == true)
    {
      event_log_info (hashcat_ctx, "# option: --optimized-kernel-enable");
    }

    if (user_options->opencl_vector_width_chgd == true)
    {
      event_log_info (hashcat_ctx, "# option: --opencl-vector-width=%u", user_options->opencl_vector_width);
    }

    if (user_options->kernel_accel_chgd == true)
    {
      event_log_info (hashcat_ctx, "# option: --kernel-accel=%u", user_options->kernel_accel);
    }
    else if (user_options->kernel_loops_chgd == true)
    {
      event_log_info (hashcat_ctx, "# option: --kernel-loops=%u", user_options->kernel_loops);
    }
    else if (user_options->kernel_threads_chgd == true)
    {
      event_log_info (hashcat_ctx, "# option: --kernel-threads=%u", user_options->kernel_threads);
    }
    else
    {
      if (user_options->workload_profile_chgd == true)
      {
        event_log_info (hashcat_ctx, "# option: --workload-profile=%u", user_options->workload_profile);
      }
    }
  }
}