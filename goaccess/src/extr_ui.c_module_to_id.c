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
#define  BROWSERS_ID 142 
#define  GEO_LOCATION_ID 141 
#define  HOSTS_ID 140 
#define  KEYPHRASES_ID 139 
#define  NOT_FOUND_ID 138 
#define  OS_ID 137 
#define  REFERRERS_ID 136 
#define  REFERRING_SITES_ID 135 
#define  REMOTE_USER_ID 134 
#define  REQUESTS_ID 133 
#define  REQUESTS_STATIC_ID 132 
#define  STATUS_CODES_ID 131 
#define  VIRTUAL_HOSTS_ID 130 
#define  VISITORS_ID 129 
#define  VISIT_TIMES_ID 128 
 char const* _ (char const*) ; 

const char *
module_to_id (GModule module)
{
  static const char *modules[] = {
    VISITORS_ID,
    REQUESTS_ID,
    REQUESTS_STATIC_ID,
    NOT_FOUND_ID,
    HOSTS_ID,
    OS_ID,
    BROWSERS_ID,
    VISIT_TIMES_ID,
    VIRTUAL_HOSTS_ID,
    REFERRERS_ID,
    REFERRING_SITES_ID,
    KEYPHRASES_ID,
    STATUS_CODES_ID,
    REMOTE_USER_ID,
#ifdef HAVE_GEOLOCATION
    GEO_LOCATION_ID,
#endif
  };

  return _(modules[module]);
}