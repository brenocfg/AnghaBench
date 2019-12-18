#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * errstr; int /*<<< orphan*/ * req; int /*<<< orphan*/ * date; int /*<<< orphan*/ * host; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 void* xstrdup (char*) ; 

__attribute__((used)) static int
verify_missing_fields (GLogItem * logitem)
{
  /* must have the following fields */
  if (logitem->host == NULL)
    logitem->errstr = xstrdup ("IPv4/6 is required.");
  else if (logitem->date == NULL)
    logitem->errstr = xstrdup ("A valid date is required.");
  else if (logitem->req == NULL)
    logitem->errstr = xstrdup ("A request is required.");

  return logitem->errstr != NULL;
}