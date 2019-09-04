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
 int /*<<< orphan*/  GeoIP_cleanup () ; 
 int /*<<< orphan*/  GeoIP_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geo_location_data ; 
 int /*<<< orphan*/  is_geoip_resource () ; 

void
geoip_free (void)
{
  if (!is_geoip_resource ())
    return;

  GeoIP_delete (geo_location_data);
  GeoIP_cleanup ();
}