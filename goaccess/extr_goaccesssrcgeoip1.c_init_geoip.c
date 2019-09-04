#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  geo_db; int /*<<< orphan*/ * geoip_database; } ;

/* Variables and functions */
 int /*<<< orphan*/  GeoIP_new (int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  geo_location_data ; 
 int /*<<< orphan*/  geoip_open_db (int /*<<< orphan*/ *) ; 

void
init_geoip (void)
{
  /* open custom city GeoIP database */
  if (conf.geoip_database != NULL)
    geo_location_data = geoip_open_db (conf.geoip_database);
  /* fall back to legacy GeoIP database */
  else
    geo_location_data = GeoIP_new (conf.geo_db);
}