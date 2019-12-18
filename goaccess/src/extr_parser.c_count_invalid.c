#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ invalid_requests_log; } ;
struct TYPE_6__ {scalar_t__ invalid; TYPE_1__* items; int /*<<< orphan*/  log_erridx; int /*<<< orphan*/ * errors; } ;
struct TYPE_5__ {scalar_t__ errstr; } ;
typedef  TYPE_2__ GLog ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INVALID (char*) ; 
 scalar_t__ MAX_LOG_ERRORS ; 
 TYPE_4__ conf ; 
 int /*<<< orphan*/  ht_insert_genstats (char*,int) ; 
 int /*<<< orphan*/ * xcalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  xstrdup (scalar_t__) ; 

__attribute__((used)) static void
count_invalid (GLog * glog, const char *line)
{
  glog->invalid++;
#ifdef TCB_BTREE
  ht_insert_genstats ("failed_requests", 1);
#endif
  if (conf.invalid_requests_log) {
    LOG_INVALID (("%s", line));
  }

  if (glog->items->errstr && glog->invalid < MAX_LOG_ERRORS) {
    if (glog->errors == NULL)
      glog->errors = xcalloc (MAX_LOG_ERRORS, sizeof (char *));
    glog->errors[glog->log_erridx++] = xstrdup (glog->items->errstr);
  }
}