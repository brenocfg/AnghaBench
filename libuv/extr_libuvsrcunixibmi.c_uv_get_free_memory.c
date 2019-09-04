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
typedef  unsigned long long uint64_t ;
struct TYPE_3__ {unsigned long long main_storage_size; unsigned long long current_unprotected_storage_used; } ;
typedef  TYPE_1__ SSTS0200 ;

/* Variables and functions */
 scalar_t__ get_ibmi_system_status (TYPE_1__*) ; 

uint64_t uv_get_free_memory(void) {
  SSTS0200 rcvr;

  if (get_ibmi_system_status(&rcvr))
    return 0;

  /* The amount of main storage, in kilobytes, in the system. */
  uint64_t main_storage_size = rcvr.main_storage_size;

  /* The current amount of storage in use for temporary objects.
   * in millions (M) of bytes.
   */
  uint64_t current_unprotected_storage_used =
    rcvr.current_unprotected_storage_used * 1024ULL;

  uint64_t free_storage_size =
    (main_storage_size - current_unprotected_storage_used) * 1024ULL;

  return free_storage_size < 0 ? 0 : free_storage_size;
}