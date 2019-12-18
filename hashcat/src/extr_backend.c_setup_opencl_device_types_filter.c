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
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  unsigned int cl_device_type ;

/* Variables and functions */
 unsigned int CL_DEVICE_TYPE_ALL ; 
 unsigned int CL_DEVICE_TYPE_CPU ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 char* hcstrdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool setup_opencl_device_types_filter (hashcat_ctx_t *hashcat_ctx, const char *opencl_device_types, cl_device_type *out)
{
  cl_device_type opencl_device_types_filter = 0;

  if (opencl_device_types)
  {
    char *device_types = hcstrdup (opencl_device_types);

    if (device_types == NULL) return false;

    char *saveptr = NULL;

    char *next = strtok_r (device_types, ",", &saveptr);

    do
    {
      const int device_type = (const int) strtol (next, NULL, 10);

      if (device_type < 1 || device_type > 3)
      {
        event_log_error (hashcat_ctx, "Invalid OpenCL device-type %d specified.", device_type);

        hcfree (device_types);

        return false;
      }

      opencl_device_types_filter |= 1U << device_type;

    } while ((next = strtok_r (NULL, ",", &saveptr)) != NULL);

    hcfree (device_types);
  }
  else
  {
    // Do not use CPU by default, this often reduces GPU performance because
    // the CPU is too busy to handle GPU synchronization

    opencl_device_types_filter = CL_DEVICE_TYPE_ALL & ~CL_DEVICE_TYPE_CPU;
  }

  *out = opencl_device_types_filter;

  return true;
}