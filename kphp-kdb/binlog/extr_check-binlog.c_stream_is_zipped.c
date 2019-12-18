#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* F; } ;
typedef  TYPE_3__ stream_t ;
struct TYPE_6__ {scalar_t__ kfs_file_type; int flags; } ;
struct TYPE_5__ {TYPE_2__* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kfs_binlog ; 
 scalar_t__ kfs_snapshot ; 

__attribute__((used)) static int stream_is_zipped (stream_t *S) {
  assert (S->F && S->F->info && (S->F->info->kfs_file_type == kfs_binlog || S->F->info->kfs_file_type == kfs_snapshot));
  return (S->F->info->flags & 16) ? 1 : 0;
}