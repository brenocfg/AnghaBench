#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ code444_as_404; } ;
struct TYPE_4__ {scalar_t__ status; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 TYPE_3__ conf ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int
is_404 (GLogItem * logitem)
{
  /* is this a 404? */
  if (logitem->status && !memcmp (logitem->status, "404", 3))
    return 1;
  /* treat 444 as 404? */
  else if (logitem->status && !memcmp (logitem->status, "444", 3) &&
           conf.code444_as_404)
    return 1;
  return 0;
}