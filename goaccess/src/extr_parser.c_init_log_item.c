#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* items; } ;
struct TYPE_7__ {long long resp_size; struct TYPE_7__* site; int /*<<< orphan*/ * userid; int /*<<< orphan*/ * vhost; int /*<<< orphan*/ * uniq_key; int /*<<< orphan*/ * time; int /*<<< orphan*/ * status; scalar_t__ serve_time; int /*<<< orphan*/ * req; int /*<<< orphan*/ * req_key; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * qstr; int /*<<< orphan*/ * protocol; int /*<<< orphan*/ * os_type; int /*<<< orphan*/ * os; int /*<<< orphan*/ * method; int /*<<< orphan*/ * keyphrase; int /*<<< orphan*/ * host; int /*<<< orphan*/ * errstr; int /*<<< orphan*/ * date; int /*<<< orphan*/ * country; int /*<<< orphan*/ * continent; int /*<<< orphan*/ * browser_type; int /*<<< orphan*/ * browser; int /*<<< orphan*/ * agent; } ;
typedef  TYPE_1__ GLogItem ;
typedef  TYPE_2__ GLog ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* xmalloc (int) ; 

GLogItem *
init_log_item (GLog * glog)
{
  GLogItem *logitem;
  glog->items = xmalloc (sizeof (GLogItem));
  logitem = glog->items;
  memset (logitem, 0, sizeof *logitem);

  logitem->agent = NULL;
  logitem->browser = NULL;
  logitem->browser_type = NULL;
  logitem->continent = NULL;
  logitem->country = NULL;
  logitem->date = NULL;
  logitem->errstr = NULL;
  logitem->host = NULL;
  logitem->keyphrase = NULL;
  logitem->method = NULL;
  logitem->os = NULL;
  logitem->os_type = NULL;
  logitem->protocol = NULL;
  logitem->qstr = NULL;
  logitem->ref = NULL;
  logitem->req_key = NULL;
  logitem->req = NULL;
  logitem->resp_size = 0LL;
  logitem->serve_time = 0;
  logitem->status = NULL;
  logitem->time = NULL;
  logitem->uniq_key = NULL;
  logitem->vhost = NULL;
  logitem->userid = NULL;

  memset (logitem->site, 0, sizeof (logitem->site));

  return logitem;
}