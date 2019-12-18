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
struct TYPE_2__ {scalar_t__ geoip_database; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  geoip_get_city (char*,char*,int) ; 
 int /*<<< orphan*/  geoip_get_continent (char*,char*,int) ; 
 int /*<<< orphan*/  geoip_get_country (char*,char*,int) ; 
 scalar_t__ invalid_ipaddr (char*,int*) ; 
 int /*<<< orphan*/  is_geoip_resource () ; 

int
set_geolocation (char *host, char *continent, char *country, char *city)
{
  int type_ip = 0;

  if (!is_geoip_resource ())
    return 1;

  if (invalid_ipaddr (host, &type_ip))
    return 1;

  geoip_get_country (host, country, type_ip);
  geoip_get_continent (host, continent, type_ip);
  if (conf.geoip_database)
    geoip_get_city (host, city, type_ip);

  return 0;
}