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
typedef  scalar_t__ const u64 ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ const status_get_progress_done (int /*<<< orphan*/  const*) ; 
 scalar_t__ const status_get_progress_rejected (int /*<<< orphan*/  const*) ; 
 scalar_t__ const status_get_progress_restored (int /*<<< orphan*/  const*) ; 

u64 status_get_progress_cur (const hashcat_ctx_t *hashcat_ctx)
{
  const u64 progress_done     = status_get_progress_done     (hashcat_ctx);
  const u64 progress_rejected = status_get_progress_rejected (hashcat_ctx);
  const u64 progress_restored = status_get_progress_restored (hashcat_ctx);

  const u64 progress_cur = progress_done + progress_rejected + progress_restored;

  return progress_cur;
}