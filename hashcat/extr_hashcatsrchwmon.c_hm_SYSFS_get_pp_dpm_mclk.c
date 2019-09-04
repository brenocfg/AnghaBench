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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HCBUFSIZ_TINY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_log_error (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  hc_asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 char* hm_SYSFS_get_syspath_device (int /*<<< orphan*/ *,int const) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int hm_SYSFS_get_pp_dpm_mclk (hashcat_ctx_t *hashcat_ctx, const int device_id, int *val)
{
  char *syspath = hm_SYSFS_get_syspath_device (hashcat_ctx, device_id);

  if (syspath == NULL) return -1;

  char *path;

  hc_asprintf (&path, "%s/pp_dpm_mclk", syspath);

  hcfree (syspath);

  FILE *fd = fopen (path, "r");

  if (fd == NULL)
  {
    event_log_error (hashcat_ctx, "%s: %s", path, strerror (errno));

    hcfree (path);

    return -1;
  }

  int clockfreq = 0;

  while (!feof (fd))
  {
    char buf[HCBUFSIZ_TINY];

    char *ptr = fgets (buf, sizeof (buf), fd);

    if (ptr == NULL) continue;

    size_t len = strlen (ptr);

    if (len < 2) continue;

    if (ptr[len - 2] != '*') continue;

    int profile = 0;

    int rc = sscanf (ptr, "%d: %dMHz", &profile, &clockfreq);

    if (rc == 2) break;
  }

  fclose (fd);

  *val = clockfreq;

  hcfree (path);

  return 0;
}