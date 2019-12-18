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
struct TYPE_4__ {int binlog_prefix_len; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ backup_file_t ;

/* Variables and functions */
 TYPE_1__* zmalloc0 (int) ; 
 int /*<<< orphan*/  zstrdup (char*) ; 

__attribute__((used)) static backup_file_t *backup_file_alloc (char *filename, int len) {
  //vkprintf (4, "%s: %s, %d\n", __func__, filename, len);
  backup_file_t *V = zmalloc0 (sizeof (backup_file_t));
  V->filename = zstrdup (filename);
  V->binlog_prefix_len = len;
  return V;
}