#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kfs_file_info {scalar_t__ file_size; TYPE_1__* replica; } ;
typedef  TYPE_1__* kfs_replica_handle_t ;
struct TYPE_6__ {char* replica_prefix; int binlog_num; int snapshot_num; struct kfs_file_info** snapshots; struct kfs_file_info** binlogs; int /*<<< orphan*/ * ctx_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_replica (TYPE_1__*) ; 
 int cmp_file_info (struct kfs_file_info*,struct kfs_file_info*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,int,int) ; 
 TYPE_1__* open_replica (char*,int) ; 
 int /*<<< orphan*/  replica_close_ctx_crypto (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int update_replica (kfs_replica_handle_t R, int force) {
  if (!R) {
    return -1;
  }
  kfs_replica_handle_t RN = open_replica (R->replica_prefix, force);
  if (!RN) {
    return -1;
  }

  replica_close_ctx_crypto (R);
  R->ctx_crypto = RN->ctx_crypto;
  RN->ctx_crypto = NULL;

  int i = 0, j = 0;
  struct kfs_file_info *FI, *FJ, **T;

  while (i < RN->binlog_num && j < R->binlog_num) {
    FI = RN->binlogs[i];
    FJ = R->binlogs[j];
    int r = cmp_file_info (FI, FJ);
    if (r < 0) {
      i++;
    } else if (r > 0) {
      j++;
    } else {
      RN->binlogs[i++] = FJ;
      R->binlogs[j++] = FI;
      assert (FJ->file_size <= FI->file_size);
      FJ->file_size = FI->file_size;
    }
  }

  i = j = 0;
  while (i < RN->snapshot_num && j < R->snapshot_num) {
    FI = RN->snapshots[i];
    FJ = R->snapshots[j];
    int r = cmp_file_info (FI, FJ);
    if (r < 0) {
      i++;
    } else if (r > 0) {
      j++;
    } else {
      RN->snapshots[i++] = FJ;
      R->snapshots[j++] = FI;
      assert (FJ->file_size <= FI->file_size);
      FJ->file_size = FI->file_size;
    }
  }

  i = R->binlog_num;  R->binlog_num = RN->binlog_num;  RN->binlog_num = i;
  T = R->binlogs;     R->binlogs = RN->binlogs;        RN->binlogs = T;

  i = R->snapshot_num;  R->snapshot_num = RN->snapshot_num;  RN->snapshot_num = i;
  T = R->snapshots;     R->snapshots = RN->snapshots;        RN->snapshots = T;

  if (verbosity > 1) {
    fprintf (stderr, "finished reloading file list for replica %s: %d binlogs, %d snapshots (OLD: %d, %d)\n",
      R->replica_prefix, R->binlog_num, R->snapshot_num, RN->binlog_num, RN->snapshot_num);
  }

  close_replica (RN);

  for (i = 0; i < R->binlog_num; i++) {
    R->binlogs[i]->replica = R;
  }

  for (i = 0; i < R->snapshot_num; i++) {
    R->snapshots[i]->replica = R;
  }

  return 1;
}