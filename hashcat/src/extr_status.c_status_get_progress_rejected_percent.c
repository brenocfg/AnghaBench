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
 scalar_t__ status_get_progress_cur (int /*<<< orphan*/  const*) ; 
 scalar_t__ status_get_progress_rejected (int /*<<< orphan*/  const*) ; 

double status_get_progress_rejected_percent (const hashcat_ctx_t *hashcat_ctx)
{
  const u64 progress_cur      = status_get_progress_cur      (hashcat_ctx);
  const u64 progress_rejected = status_get_progress_rejected (hashcat_ctx);

  double percent_rejected = 0;

  if (progress_cur)
  {
    percent_rejected = ((double) (progress_rejected) / (double) progress_cur) * 100;
  }

  return percent_rejected;
}