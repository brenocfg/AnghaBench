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

__attribute__((used)) static bool setup_backend_devices_filter (hashcat_ctx_t *hashcat_ctx, const char *backend_devices, u64 *out)
{
  u64 backend_devices_filter = 0;

  if (backend_devices)
  {
    char *devices = hcstrdup (backend_devices);

    if (devices == NULL) return false;

    char *saveptr = NULL;

    char *next = strtok_r (devices, ",", &saveptr);

    do
    {
      const int backend_device_id = (const int) strtol (next, NULL, 10);

      if ((backend_device_id <= 0) || (backend_device_id >= 64))
      {
        event_log_error (hashcat_ctx, "Invalid device_id %d specified.", backend_device_id);

        hcfree (devices);

        return false;
      }

      backend_devices_filter |= 1ULL << (backend_device_id - 1);

    } while ((next = strtok_r ((char *) NULL, ",", &saveptr)) != NULL);

    hcfree (devices);
  }
  else
  {
    backend_devices_filter = -1ULL;
  }

  *out = backend_devices_filter;

  return true;
}