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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int HCBUFSIZ_TINY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_feof (int /*<<< orphan*/ *) ; 
 char* hc_fgets (char*,int,int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 char* hm_SYSFS_get_syspath_device (int /*<<< orphan*/ *,int const) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int hm_SYSFS_get_pp_dpm_mclk (hashcat_ctx_t *hashcat_ctx, const int backend_device_idx, int *val)
{
  char *syspath = hm_SYSFS_get_syspath_device (hashcat_ctx, backend_device_idx);

  if (syspath == NULL) return -1;

  char *path;

  hc_asprintf (&path, "%s/pp_dpm_mclk", syspath);

  hcfree (syspath);

  HCFILE fp;

  if (hc_fopen (&fp, path, "r") == false)
  {
    event_log_error (hashcat_ctx, "%s: %s", path, strerror (errno));

    hcfree (path);

    return -1;
  }

  int clockfreq = 0;

  while (!hc_feof (&fp))
  {
    char buf[HCBUFSIZ_TINY];

    char *ptr = hc_fgets (buf, sizeof (buf), &fp);

    if (ptr == NULL) continue;

    size_t len = strlen (ptr);

    if (len < 2) continue;

    if (ptr[len - 2] != '*') continue;

    int profile = 0;

    int rc = sscanf (ptr, "%d: %dMHz", &profile, &clockfreq);

    if (rc == 2) break;
  }

  hc_fclose (&fp);

  *val = clockfreq;

  hcfree (path);

  return 0;
}