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
 int /*<<< orphan*/  COUNTRY_LEN ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void
geoip_set_country (const char *country, const char *code, char *loc)
{
  if (country && code)
    snprintf (loc, COUNTRY_LEN, "%s %s", code, country);
  else
    snprintf (loc, COUNTRY_LEN, "%s", "Unknown");
}