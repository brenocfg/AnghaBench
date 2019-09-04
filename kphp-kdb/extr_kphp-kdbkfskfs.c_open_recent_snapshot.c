#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kfs_file {int dummy; } ;
typedef  TYPE_1__* kfs_replica_handle_t ;
typedef  struct kfs_file* kfs_file_handle_t ;
struct TYPE_4__ {int snapshot_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct kfs_file* open_snapshot (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

kfs_file_handle_t open_recent_snapshot (kfs_replica_handle_t R) {
  if (!R) {
    return 0;
  }
  if (verbosity > 1) {
    fprintf (stderr, "opening last snapshot file\n");
  }

  struct kfs_file *F = 0;
  int p = R->snapshot_num - 1;
  while (p >= 0 && (F = open_snapshot (R, p)) == 0) {
    --p;
  }
  return F;
}