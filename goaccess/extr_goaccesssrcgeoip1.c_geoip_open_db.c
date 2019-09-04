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
typedef  int /*<<< orphan*/  GeoIP ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char const*) ; 
 int /*<<< orphan*/  GEOIP_CHARSET_UTF8 ; 
 int /*<<< orphan*/  GEOIP_MEMORY_CACHE ; 
 int /*<<< orphan*/ * GeoIP_open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GeoIP_set_charset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 

__attribute__((used)) static GeoIP *
geoip_open_db (const char *db)
{
  GeoIP *geoip;
  geoip = GeoIP_open (db, GEOIP_MEMORY_CACHE);

  if (geoip == NULL)
    FATAL ("Unable to open GeoIP database: %s\n", db);

  GeoIP_set_charset (geoip, GEOIP_CHARSET_UTF8);
  LOG_DEBUG (("Opened GeoIP City database: %s\n", db));

  return geoip;
}