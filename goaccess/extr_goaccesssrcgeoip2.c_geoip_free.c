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

/* Variables and functions */
 int /*<<< orphan*/  MMDB_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_geoip_resource () ; 
 int /*<<< orphan*/ * mmdb ; 

void
geoip_free (void)
{
  if (!is_geoip_resource ())
    return;

  MMDB_close (mmdb);
  free (mmdb);
  mmdb = NULL;
}