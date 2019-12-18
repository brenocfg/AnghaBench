#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kfs_file_handle_t ;
struct TYPE_6__ {TYPE_1__* info; } ;
struct TYPE_5__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 

int load_index (kfs_file_handle_t Index) {
  assert (Index);
  kprintf ("fatal: cannot load index %s\n", Index->info->filename);
  return 7;
}