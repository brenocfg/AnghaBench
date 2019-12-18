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
#define  BROWSERS_LABEL 142 
#define  GEO_LOCATION_LABEL 141 
#define  HOSTS_LABEL 140 
#define  KEYPHRASES_LABEL 139 
#define  NOT_FOUND_LABEL 138 
#define  OS_LABEL 137 
#define  REFERRERS_LABEL 136 
#define  REFERRING_SITES_LABEL 135 
#define  REMOTE_USER_LABEL 134 
#define  REQUESTS_LABEL 133 
#define  REQUESTS_STATIC_LABEL 132 
#define  STATUS_CODES_LABEL 131 
#define  VIRTUAL_HOSTS_LABEL 130 
#define  VISITORS_LABEL 129 
#define  VISIT_TIMES_LABEL 128 
 char const* _ (char const*) ; 

const char *
module_to_label (GModule module)
{
  static const char *modules[] = {
    VISITORS_LABEL,
    REQUESTS_LABEL,
    REQUESTS_STATIC_LABEL,
    NOT_FOUND_LABEL,
    HOSTS_LABEL,
    OS_LABEL,
    BROWSERS_LABEL,
    VISIT_TIMES_LABEL,
    VIRTUAL_HOSTS_LABEL,
    REFERRERS_LABEL,
    REFERRING_SITES_LABEL,
    KEYPHRASES_LABEL,
    STATUS_CODES_LABEL,
    REMOTE_USER_LABEL,
#ifdef HAVE_GEOLOCATION
    GEO_LOCATION_LABEL,
#endif
  };

  return _(modules[module]);
}