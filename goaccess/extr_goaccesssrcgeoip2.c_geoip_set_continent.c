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
 int /*<<< orphan*/  CONTINENT_LEN ; 
 char* get_continent_name_and_code (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
geoip_set_continent (const char *continent, char *loc)
{
  if (continent)
    snprintf (loc, CONTINENT_LEN, "%s",
              get_continent_name_and_code (continent));
  else
    snprintf (loc, CONTINENT_LEN, "%s", "Unknown");
}