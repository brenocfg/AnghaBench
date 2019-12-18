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
typedef  int /*<<< orphan*/  kfs_snapshot_write_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kfs_sws_crypt (int /*<<< orphan*/ *,void*,long long) ; 
 int /*<<< orphan*/  kfs_sws_write (int /*<<< orphan*/ *,void*,long long) ; 

void kfs_sws_safe_write (kfs_snapshot_write_stream_t *S, const void *buff, long long count) {
  assert (count >= 0);
  if (!count) {
    return;
  }
  kfs_sws_write (S, (void *) buff, count);
  kfs_sws_crypt (S, (void *) buff, count); /* restore buff */
}