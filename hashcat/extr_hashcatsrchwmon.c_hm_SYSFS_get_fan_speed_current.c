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

__attribute__((used)) static int hm_SYSFS_get_fan_speed_current (hashcat_ctx_t *hashcat_ctx, const int device_id, int *val)
{
  char *syspath = hm_SYSFS_get_syspath_hwmon (hashcat_ctx, device_id);

  if (syspath == NULL) return -1;

  char *path_cur;
  char *path_max;

  hc_asprintf (&path_cur, "%s/pwm1",     syspath);
  hc_asprintf (&path_max, "%s/pwm1_max", syspath);

  hcfree (syspath);

  FILE *fd_cur = fopen (path_cur, "r");

  if (fd_cur == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", path_cur, strerror (errno));

    hcfree (path_cur);
    hcfree (path_max);

    return -1;
  }

  int pwm1_cur = 0;

  if (fscanf (fd_cur, "%d", &pwm1_cur) != 1)
  {
    fclose (fd_cur);

    event_log_error (hashcat_ctx, "%s: unexpected data.", path_cur);

    hcfree (path_cur);
    hcfree (path_max);

    return -1;
  }

  fclose (fd_cur);

  FILE *fd_max = fopen (path_max, "r");

  if (fd_max == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", path_max, strerror (errno));

    hcfree (path_cur);
    hcfree (path_max);

    return -1;
  }

  int pwm1_max = 0;

  if (fscanf (fd_max, "%d", &pwm1_max) != 1)
  {
    fclose (fd_max);

    event_log_error (hashcat_ctx, "%s: unexpected data.", path_max);

    hcfree (path_cur);
    hcfree (path_max);

    return -1;
  }

  fclose (fd_max);

  if (pwm1_max == 0)
  {
    event_log_error (hashcat_ctx, "%s: pwm1_max cannot be 0.", path_max);

    hcfree (path_cur);
    hcfree (path_max);

    return -1;
  }

  const float p1 = (float) pwm1_max / 100.0f;

  const float pwm1_percent = (float) pwm1_cur / p1;

  *val = (int) pwm1_percent;

  hcfree (path_cur);
  hcfree (path_max);

  return 0;
}