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
typedef  TYPE_1__* kfs_file_handle_t ;
struct TYPE_4__ {int fd; scalar_t__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  file_info_decref (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int kfs_close_file (kfs_file_handle_t F, int close_handle) {
  if (!F) {
    return 0;
  }
  if (F->fd >= 0) {
    if (close_handle) {
      assert (close (F->fd) >= 0);
    }
    F->fd = -1;
  }
  if (F->info) {
    file_info_decref (F->info);
    F->info = 0;
  }
  free (F);
  return 0;
}