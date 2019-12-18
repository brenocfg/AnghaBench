#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ status_get_restore_point (int /*<<< orphan*/  const*) ; 
 scalar_t__ status_get_restore_total (int /*<<< orphan*/  const*) ; 

double status_get_restore_percent (const hashcat_ctx_t *hashcat_ctx)
{
  double restore_percent = 0;

  const u64 restore_point = status_get_restore_point (hashcat_ctx);
  const u64 restore_total = status_get_restore_total (hashcat_ctx);

  if (restore_total > 0)
  {
    restore_percent = ((double) restore_point / (double) restore_total) * 100;
  }

  return restore_percent;
}