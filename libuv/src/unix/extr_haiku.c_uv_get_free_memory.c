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
typedef  int uint64_t ;
struct TYPE_3__ {int max_pages; int used_pages; } ;
typedef  TYPE_1__ system_info ;
typedef  scalar_t__ status_t ;

/* Variables and functions */
 scalar_t__ B_OK ; 
 int B_PAGE_SIZE ; 
 scalar_t__ get_system_info (TYPE_1__*) ; 

uint64_t uv_get_free_memory(void) {
  status_t status;
  system_info sinfo;

  status = get_system_info(&sinfo);
  if (status != B_OK)
    return 0;

  return (sinfo.max_pages - sinfo.used_pages) * B_PAGE_SIZE;
}