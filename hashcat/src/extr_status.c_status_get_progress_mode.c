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
 int PROGRESS_MODE_KEYSPACE_KNOWN ; 
 int PROGRESS_MODE_KEYSPACE_UNKNOWN ; 
 scalar_t__ status_get_progress_end_relative_skip (int /*<<< orphan*/  const*) ; 

int status_get_progress_mode (const hashcat_ctx_t *hashcat_ctx)
{
  const u64 progress_end_relative_skip = status_get_progress_end_relative_skip (hashcat_ctx);

  if (progress_end_relative_skip > 0)
  {
    return PROGRESS_MODE_KEYSPACE_KNOWN;
  }
  return PROGRESS_MODE_KEYSPACE_UNKNOWN;
}