#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* vhost; struct TYPE_4__* userid; struct TYPE_4__* uniq_key; struct TYPE_4__* time; struct TYPE_4__* status; struct TYPE_4__* req; struct TYPE_4__* req_key; struct TYPE_4__* ref; struct TYPE_4__* qstr; struct TYPE_4__* protocol; struct TYPE_4__* os_type; struct TYPE_4__* os; struct TYPE_4__* method; struct TYPE_4__* keyphrase; struct TYPE_4__* host; struct TYPE_4__* errstr; struct TYPE_4__* date; struct TYPE_4__* country; struct TYPE_4__* continent; struct TYPE_4__* browser_type; struct TYPE_4__* browser; struct TYPE_4__* agent; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
free_glog (GLogItem * logitem)
{
  if (logitem->agent != NULL)
    free (logitem->agent);
  if (logitem->browser != NULL)
    free (logitem->browser);
  if (logitem->browser_type != NULL)
    free (logitem->browser_type);
  if (logitem->continent != NULL)
    free (logitem->continent);
  if (logitem->country != NULL)
    free (logitem->country);
  if (logitem->date != NULL)
    free (logitem->date);
  if (logitem->errstr != NULL)
    free (logitem->errstr);
  if (logitem->host != NULL)
    free (logitem->host);
  if (logitem->keyphrase != NULL)
    free (logitem->keyphrase);
  if (logitem->method != NULL)
    free (logitem->method);
  if (logitem->os != NULL)
    free (logitem->os);
  if (logitem->os_type != NULL)
    free (logitem->os_type);
  if (logitem->protocol != NULL)
    free (logitem->protocol);
  if (logitem->qstr != NULL)
    free (logitem->qstr);
  if (logitem->ref != NULL)
    free (logitem->ref);
  if (logitem->req_key != NULL)
    free (logitem->req_key);
  if (logitem->req != NULL)
    free (logitem->req);
  if (logitem->status != NULL)
    free (logitem->status);
  if (logitem->time != NULL)
    free (logitem->time);
  if (logitem->uniq_key != NULL)
    free (logitem->uniq_key);
  if (logitem->userid != NULL)
    free (logitem->userid);
  if (logitem->vhost != NULL)
    free (logitem->vhost);

  free (logitem);
}