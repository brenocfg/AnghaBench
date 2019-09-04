#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kfs_file_handle_t ;
struct TYPE_5__ {TYPE_1__* info; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,int,...) ; 
 int load_binlogpos (int) ; 
 int tar_unpack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_dir ; 

__attribute__((used)) static int load_index (kfs_file_handle_t Index) {
  if (Index == NULL) {
    return 0;
  }
  int r = tar_unpack (Index->fd, work_dir);
  if (r < 0) {
    kprintf ("tar_unpack (%s, %s) returns error code %d.\n", Index->info->filename, work_dir, r);
    exit (1);
  }
  r = load_binlogpos (1);
  if (r < 0) {
    kprintf ("load_binlogpos () returns error code %d.\n", r);
    exit (1);
  }
  return 0;
}