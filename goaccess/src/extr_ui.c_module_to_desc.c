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
typedef  size_t GModule ;

/* Variables and functions */
#define  BROWSERS_DESC 142 
#define  GEO_LOCATION_DESC 141 
#define  HOSTS_DESC 140 
#define  KEYPHRASES_DESC 139 
#define  NOT_FOUND_DESC 138 
#define  OS_DESC 137 
#define  REFERRERS_DESC 136 
#define  REFERRING_SITES_DESC 135 
#define  REMOTE_USER_DESC 134 
#define  REQUESTS_DESC 133 
#define  REQUESTS_STATIC_DESC 132 
#define  STATUS_CODES_DESC 131 
#define  VIRTUAL_HOSTS_DESC 130 
#define  VISITORS_DESC 129 
#define  VISIT_TIMES_DESC 128 
 char const* _ (char const*) ; 

const char *
module_to_desc (GModule module)
{
  static const char *modules[] = {
    VISITORS_DESC,
    REQUESTS_DESC,
    REQUESTS_STATIC_DESC,
    NOT_FOUND_DESC,
    HOSTS_DESC,
    OS_DESC,
    BROWSERS_DESC,
    VISIT_TIMES_DESC,
    VIRTUAL_HOSTS_DESC,
    REFERRERS_DESC,
    REFERRING_SITES_DESC,
    KEYPHRASES_DESC,
    STATUS_CODES_DESC,
    REMOTE_USER_DESC,
#ifdef HAVE_GEOLOCATION
    GEO_LOCATION_DESC,
#endif
  };

  return _(modules[module]);
}