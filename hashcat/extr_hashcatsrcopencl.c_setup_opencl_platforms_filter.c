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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 char* hcstrdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool setup_opencl_platforms_filter (hashcat_ctx_t *hashcat_ctx, const char *opencl_platforms, u64 *out)
{
  u64 opencl_platforms_filter = 0;

  if (opencl_platforms)
  {
    char *platforms = hcstrdup (opencl_platforms);

    if (platforms == NULL) return false;

    char *saveptr = NULL;

    char *next = strtok_r (platforms, ",", &saveptr);

    do
    {
      const int platform = (const int) strtol (next, NULL, 10);

      if (platform <= 0 || platform >= 64)
      {
        event_log_error (hashcat_ctx, "Invalid OpenCL platform %d specified.", platform);

        hcfree (platforms);

        return false;
      }

      opencl_platforms_filter |= 1ULL << (platform - 1);

    } while ((next = strtok_r ((char *) NULL, ",", &saveptr)) != NULL);

    hcfree (platforms);
  }
  else
  {
    opencl_platforms_filter = -1ULL;
  }

  *out = opencl_platforms_filter;

  return true;
}