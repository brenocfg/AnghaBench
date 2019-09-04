#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* geoip_database; } ;
struct TYPE_7__ {int /*<<< orphan*/  database_type; } ;
struct TYPE_8__ {TYPE_1__ metadata; } ;
typedef  int /*<<< orphan*/  MMDB_s ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,char const*) ; 
 int /*<<< orphan*/  MMDB_MODE_MMAP ; 
 int MMDB_SUCCESS ; 
 int MMDB_open (char const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_5__ conf ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int geoip_city_type ; 
 TYPE_2__* mmdb ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* xcalloc (int,int) ; 

void
init_geoip (void)
{
  const char *fn = conf.geoip_database;
  int status = 0;

  if (fn == NULL)
    return;

  /* open custom city GeoIP database */
  mmdb = xcalloc (1, sizeof (MMDB_s));
  if ((status = MMDB_open (fn, MMDB_MODE_MMAP, mmdb)) != MMDB_SUCCESS) {
    free (mmdb);
    FATAL ("Unable to open GeoIP2 database: %s\n", fn);
  }

  if (strcmp (mmdb->metadata.database_type, "GeoLite2-City") == 0)
    geoip_city_type = 1;
}