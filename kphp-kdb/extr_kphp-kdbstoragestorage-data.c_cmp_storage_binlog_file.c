#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; scalar_t__ priority; scalar_t__ dir_id; } ;
typedef  TYPE_1__ storage_binlog_file_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_storage_binlog_file (const void *x, const void *y) {
  const storage_binlog_file_t *a = *(const storage_binlog_file_t **) x;
  const storage_binlog_file_t *b = *(const storage_binlog_file_t **) y;
  if (a->size > b->size) {
    return -1;
  }
  if (a->size < b->size) {
    return 1;
  }
  if (a->priority < b->priority) {
    return -1;
  }
  if (a->priority > b->priority) {
    return 1;
  }
  if (a->dir_id < b->dir_id) {
    return -1;
  }
  if (a->dir_id > b->dir_id) {
    return 1;
  }
  return 0;
}