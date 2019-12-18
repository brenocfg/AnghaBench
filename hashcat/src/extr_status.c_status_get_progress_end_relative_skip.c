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
 scalar_t__ status_get_progress_end (int /*<<< orphan*/  const*) ; 
 scalar_t__ status_get_progress_skip (int /*<<< orphan*/  const*) ; 

u64 status_get_progress_end_relative_skip (const hashcat_ctx_t *hashcat_ctx)
{
  const u64 progress_skip = status_get_progress_skip (hashcat_ctx);
  const u64 progress_end  = status_get_progress_end  (hashcat_ctx);

  u64 progress_end_relative_skip = 0;

  if (progress_end > 0)
  {
    progress_end_relative_skip = progress_end - progress_skip;
  }

  return progress_end_relative_skip;
}