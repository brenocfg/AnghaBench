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
 int /*<<< orphan*/  format_speed_display (double const,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hcmalloc (int /*<<< orphan*/ ) ; 
 double status_get_hashes_msec_dev (int /*<<< orphan*/  const*,int const) ; 

char *status_get_speed_sec_dev (const hashcat_ctx_t *hashcat_ctx, const int backend_devices_idx)
{
  const double hashes_msec_dev = status_get_hashes_msec_dev (hashcat_ctx, backend_devices_idx);

  char *display = (char *) hcmalloc (HCBUFSIZ_TINY);

  format_speed_display (hashes_msec_dev * 1000, display, HCBUFSIZ_TINY);

  return display;
}