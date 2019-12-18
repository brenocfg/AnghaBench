#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ store_accumulated_time; } ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  OVERALL_GENTIME ; 
 TYPE_1__ conf ; 
 scalar_t__ end_proc ; 
 scalar_t__ ht_get_genstats (char*) ; 
 int /*<<< orphan*/  pskeyu64val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ start_proc ; 

__attribute__((used)) static void
poverall_processed_time (GJSON * json, int sp)
{
  uint64_t elapsed_proc = end_proc - start_proc;

#ifdef TCB_BTREE
  if (conf.store_accumulated_time)
    elapsed_proc = (uint64_t) ht_get_genstats ("accumulated_time");
#endif

  pskeyu64val (json, OVERALL_GENTIME, elapsed_proc, sp, 0);
}