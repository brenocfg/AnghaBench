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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int has_geocountry; int has_geocity; scalar_t__ output_stdout; scalar_t__ enable_html_resolver; } ;
struct TYPE_8__ {size_t idx; int /*<<< orphan*/  sub_items_size; TYPE_2__* items; int /*<<< orphan*/  module; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sub_list; TYPE_1__* metrics; } ;
struct TYPE_6__ {char* data; } ;
typedef  int /*<<< orphan*/  GSubList ;
typedef  int /*<<< orphan*/  GMetrics ;
typedef  TYPE_3__ GHolder ;

/* Variables and functions */
 int CITY_LEN ; 
 int CONTINENT_LEN ; 
 int COUNTRY_LEN ; 
 int /*<<< orphan*/  MTRC_ID_CITY ; 
 int /*<<< orphan*/  MTRC_ID_COUNTRY ; 
 int /*<<< orphan*/  MTRC_ID_HOSTNAME ; 
 int /*<<< orphan*/  add_sub_item_back (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ conf ; 
 int /*<<< orphan*/  free (char*) ; 
 char* reverse_ip (char*) ; 
 int /*<<< orphan*/  set_geolocation (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  set_host_child_metrics (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
set_host_sub_list (GHolder * h, GSubList * sub_list)
{
  GMetrics *nmetrics;
#ifdef HAVE_GEOLOCATION
  char city[CITY_LEN] = "";
  char continent[CONTINENT_LEN] = "";
  char country[COUNTRY_LEN] = "";
#endif

  char *host = h->items[h->idx].metrics->data, *hostname = NULL;
#ifdef HAVE_GEOLOCATION
  /* add geolocation child nodes */
  set_geolocation (host, continent, country, city);

  /* country */
  if (country[0] != '\0') {
    set_host_child_metrics (country, MTRC_ID_COUNTRY, &nmetrics);
    add_sub_item_back (sub_list, h->module, nmetrics);
    h->items[h->idx].sub_list = sub_list;
    h->sub_items_size++;

    /* flag only */
    conf.has_geocountry = 1;
  }

  /* city */
  if (city[0] != '\0') {
    set_host_child_metrics (city, MTRC_ID_CITY, &nmetrics);
    add_sub_item_back (sub_list, h->module, nmetrics);
    h->items[h->idx].sub_list = sub_list;
    h->sub_items_size++;

    /* flag only */
    conf.has_geocity = 1;
  }
#endif

  /* hostname */
  if (conf.enable_html_resolver && conf.output_stdout) {
    hostname = reverse_ip (host);
    set_host_child_metrics (hostname, MTRC_ID_HOSTNAME, &nmetrics);
    add_sub_item_back (sub_list, h->module, nmetrics);
    h->items[h->idx].sub_list = sub_list;
    h->sub_items_size++;
    free (hostname);
  }
}