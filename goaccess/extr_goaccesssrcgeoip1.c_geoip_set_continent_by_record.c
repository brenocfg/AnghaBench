#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * geoip_database; } ;
struct TYPE_5__ {char* continent_code; } ;
typedef  TYPE_1__ GeoIPRecord ;
typedef  int /*<<< orphan*/  GTypeIP ;

/* Variables and functions */
 int /*<<< orphan*/  GeoIPRecord_delete (TYPE_1__*) ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/ * geo_location_data ; 
 int /*<<< orphan*/  geoip_set_continent (char const*,char*) ; 
 TYPE_1__* get_geoip_record (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
geoip_set_continent_by_record (const char *ip, char *location, GTypeIP type_ip)
{
  GeoIPRecord *rec = NULL;
  const char *continent = NULL, *addr = ip;

  if (conf.geoip_database == NULL || geo_location_data == NULL)
    return;

  /* Custom GeoIP database */
  if ((rec = get_geoip_record (addr, type_ip)))
    continent = rec->continent_code;

  geoip_set_continent (continent, location);
  if (rec != NULL) {
    GeoIPRecord_delete (rec);
  }
}