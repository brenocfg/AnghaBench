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
struct TYPE_2__ {int /*<<< orphan*/  ignore_crawlers; } ;
typedef  size_t GModule ;

/* Variables and functions */
#define  BROWSERS_HEAD 142 
#define  GEO_LOCATION_HEAD 141 
#define  HOSTS_HEAD 140 
#define  KEYPHRASES_HEAD 139 
#define  NOT_FOUND_HEAD 138 
#define  OS_HEAD 137 
#define  REFERRERS_HEAD 136 
#define  REFERRING_SITES_HEAD 135 
#define  REMOTE_USER_HEAD 134 
#define  REQUESTS_HEAD 133 
#define  REQUESTS_STATIC_HEAD 132 
#define  STATUS_CODES_HEAD 131 
#define  VIRTUAL_HOSTS_HEAD 130 
 size_t VISITORS ; 
#define  VISITORS_HEAD 129 
 char* VISITORS_HEAD_BOTS ; 
#define  VISIT_TIMES_HEAD 128 
 char const* _ (char const*) ; 
 TYPE_1__ conf ; 

const char *
module_to_head (GModule module)
{
  static const char *modules[] = {
    VISITORS_HEAD,
    REQUESTS_HEAD,
    REQUESTS_STATIC_HEAD,
    NOT_FOUND_HEAD,
    HOSTS_HEAD,
    OS_HEAD,
    BROWSERS_HEAD,
    VISIT_TIMES_HEAD,
    VIRTUAL_HOSTS_HEAD,
    REFERRERS_HEAD,
    REFERRING_SITES_HEAD,
    KEYPHRASES_HEAD,
    STATUS_CODES_HEAD,
    REMOTE_USER_HEAD,
#ifdef HAVE_GEOLOCATION
    GEO_LOCATION_HEAD,
#endif
  };

  if (!conf.ignore_crawlers)
    modules[VISITORS] = VISITORS_HEAD_BOTS;

  return _(modules[module]);
}