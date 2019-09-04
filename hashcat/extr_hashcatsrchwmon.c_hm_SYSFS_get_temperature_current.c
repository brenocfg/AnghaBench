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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 char* hm_SYSFS_get_syspath_hwmon (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hm_SYSFS_get_temperature_current (hashcat_ctx_t *hashcat_ctx, const int device_id, int *val)
{
  char *syspath = hm_SYSFS_get_syspath_hwmon (hashcat_ctx, device_id);

  if (syspath == NULL) return -1;

  char *path;

  hc_asprintf (&path, "%s/temp1_input", syspath);

  hcfree (syspath);

  FILE *fd = fopen (path, "r");

  if (fd == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", path, strerror (errno));

    hcfree (path);

    return -1;
  }

  int temperature = 0;

  if (fscanf (fd, "%d", &temperature) != 1)
  {
    fclose (fd);

    event_log_error (hashcat_ctx, "%s: unexpected data.", path);

    hcfree (path);

    return -1;
  }

  fclose (fd);

  *val = temperature / 1000;

  hcfree (path);

  return 0;
}