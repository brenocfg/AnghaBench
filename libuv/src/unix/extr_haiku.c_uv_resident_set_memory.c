#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  team; } ;
typedef  TYPE_1__ thread_info ;
typedef  scalar_t__ status_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {scalar_t__ ram_size; } ;
typedef  TYPE_2__ area_info ;

/* Variables and functions */
 scalar_t__ B_OK ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  find_thread (int /*<<< orphan*/ *) ; 
 scalar_t__ get_next_area_info (int /*<<< orphan*/ ,scalar_t__*,TYPE_2__*) ; 
 scalar_t__ get_thread_info (int /*<<< orphan*/ ,TYPE_1__*) ; 

int uv_resident_set_memory(size_t* rss) {
  area_info area;
  ssize_t cookie;
  status_t status;
  thread_info thread;

  status = get_thread_info(find_thread(NULL), &thread);
  if (status != B_OK)
    return UV__ERR(status);

  cookie = 0;
  *rss = 0;
  while (get_next_area_info(thread.team, &cookie, &area) == B_OK)
    *rss += area.ram_size;

  return 0;
}