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
typedef  int /*<<< orphan*/  MMDB_lookup_result_s ;

/* Variables and functions */
 scalar_t__ geoip_city_type ; 
 int /*<<< orphan*/  geoip_lookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  geoip_query_city (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  geoip_query_continent (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  geoip_query_country (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_geoip_resource () ; 

int
set_geolocation (char *host, char *continent, char *country, char *city)
{
  MMDB_lookup_result_s res;

  if (!is_geoip_resource ())
    return 1;

  geoip_lookup (&res, host);
  geoip_query_country (res, country);
  geoip_query_continent (res, continent);
  if (geoip_city_type)
    geoip_query_city (res, city);

  return 0;
}