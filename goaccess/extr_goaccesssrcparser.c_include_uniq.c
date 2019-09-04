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
struct TYPE_5__ {int client_err_to_unique_count; } ;
struct TYPE_4__ {char* status; } ;
typedef  TYPE_1__ GLogItem ;

/* Variables and functions */
 TYPE_3__ conf ; 

__attribute__((used)) static int
include_uniq (GLogItem * logitem)
{
  int u = conf.client_err_to_unique_count;

  if (!logitem->status || logitem->status[0] != '4' ||
      (u && logitem->status[0] == '4'))
    return 1;
  return 0;
}