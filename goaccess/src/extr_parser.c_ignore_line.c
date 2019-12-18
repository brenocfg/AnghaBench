#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ignore_statics; scalar_t__ ignore_qstr; } ;
struct TYPE_5__ {int /*<<< orphan*/  req; int /*<<< orphan*/  status; int /*<<< orphan*/  site; int /*<<< orphan*/  agent; } ;
typedef  TYPE_1__ GLogItem ;
typedef  int /*<<< orphan*/  GLog ;

/* Variables and functions */
 int IGNORE_LEVEL_PANEL ; 
 TYPE_4__ conf ; 
 scalar_t__ excluded_ip (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ handle_crawler (int /*<<< orphan*/ ) ; 
 scalar_t__ ignore_referer (int /*<<< orphan*/ ) ; 
 scalar_t__ ignore_static (int /*<<< orphan*/ ) ; 
 scalar_t__ ignore_status_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_qstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ignore_line (GLog * glog, GLogItem * logitem)
{
  if (excluded_ip (glog, logitem) == 0)
    return IGNORE_LEVEL_PANEL;
  if (handle_crawler (logitem->agent) == 0)
    return IGNORE_LEVEL_PANEL;
  if (ignore_referer (logitem->site))
    return IGNORE_LEVEL_PANEL;
  if (ignore_status_code (logitem->status))
    return IGNORE_LEVEL_PANEL;
  if (ignore_static (logitem->req))
    return conf.ignore_statics; // IGNORE_LEVEL_PANEL or IGNORE_LEVEL_REQ

  /* check if we need to remove the request's query string */
  if (conf.ignore_qstr)
    strip_qstring (logitem->req);

  return 0;
}