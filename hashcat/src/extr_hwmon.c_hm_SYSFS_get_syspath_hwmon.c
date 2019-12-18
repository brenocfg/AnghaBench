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

/* Variables and functions */
 int /*<<< orphan*/  HCBUFSIZ_TINY ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*) ; 
 char* first_file_in_directory (char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 char* hm_SYSFS_get_syspath_device (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static char *hm_SYSFS_get_syspath_hwmon (hashcat_ctx_t *hashcat_ctx, const int backend_device_idx)
{
  char *syspath = hm_SYSFS_get_syspath_device (hashcat_ctx, backend_device_idx);

  if (syspath == NULL)
  {
    event_log_error (hashcat_ctx, "hm_SYSFS_get_syspath_device() failed.");

    return NULL;
  }

  char *hwmon = (char *) hcmalloc (HCBUFSIZ_TINY);

  snprintf (hwmon, HCBUFSIZ_TINY, "%s/hwmon", syspath);

  char *hwmonN = first_file_in_directory (hwmon);

  if (hwmonN == NULL)
  {
    event_log_error (hashcat_ctx, "First_file_in_directory() failed.");

    hcfree (syspath);

    hcfree (hwmon);
    hcfree (hwmonN);

    return NULL;
  }

  snprintf (hwmon, HCBUFSIZ_TINY, "%s/hwmon/%s", syspath, hwmonN);

  hcfree (syspath);

  hcfree (hwmonN);

  return hwmon;
}