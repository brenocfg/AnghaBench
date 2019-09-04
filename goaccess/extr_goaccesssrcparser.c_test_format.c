#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int log_erridx; int /*<<< orphan*/ * errors; } ;
typedef  TYPE_1__ GLog ;

/* Variables and functions */
 int /*<<< orphan*/  free_logerrors (TYPE_1__*) ; 
 scalar_t__ parse_log (TYPE_1__**,int /*<<< orphan*/ *,int) ; 
 char** xcalloc (int,int) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

char **
test_format (GLog * glog, int *len)
{
  char **errors = NULL;
  int i;

  if (parse_log (&glog, NULL, 1) == 0)
    goto clean;

  errors = xcalloc (glog->log_erridx, sizeof (char *));
  for (i = 0; i < glog->log_erridx; ++i)
    errors[i] = xstrdup (glog->errors[i]);
  *len = glog->log_erridx;

clean:
  free_logerrors (glog);

  return errors;
}