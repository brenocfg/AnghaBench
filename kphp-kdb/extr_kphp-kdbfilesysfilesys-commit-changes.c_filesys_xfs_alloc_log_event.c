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
typedef  int /*<<< orphan*/  lev_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_FILESYS_XFS_BEGIN_TRANSACTION ; 
 int /*<<< orphan*/  events ; 
 void* memory_alloc_log_event (int /*<<< orphan*/ ,int) ; 
 int transaction_id ; 

__attribute__((used)) static void *filesys_xfs_alloc_log_event (lev_type_t type, int size) {
  if (!events) {
    int *p = memory_alloc_log_event (LEV_FILESYS_XFS_BEGIN_TRANSACTION, 8);
    p[1] = transaction_id;
  }
  return memory_alloc_log_event (type, size);
}