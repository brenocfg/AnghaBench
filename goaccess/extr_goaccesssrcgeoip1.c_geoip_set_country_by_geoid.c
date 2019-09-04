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
typedef  int /*<<< orphan*/  GTypeIP ;

/* Variables and functions */
 char* GeoIP_code_by_id (int) ; 
 char* geoip_get_country_by_geoid (char const*,int /*<<< orphan*/ ) ; 
 int geoip_get_geoid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geoip_set_country (char const*,char const*,char*) ; 
 int /*<<< orphan*/  is_geoip_resource () ; 

__attribute__((used)) static void
geoip_set_country_by_geoid (const char *ip, char *location, GTypeIP type_ip)
{
  const char *country = NULL, *code = NULL, *addr = ip;
  int geoid = 0;

  if (!is_geoip_resource ())
    return;

  if (!(country = geoip_get_country_by_geoid (addr, type_ip)))
    goto out;

  /* return two letter country code */
  if (!(geoid = geoip_get_geoid (addr, type_ip)))
    goto out;
  code = GeoIP_code_by_id (geoid);

out:
  geoip_set_country (country, code, location);
}