#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; scalar_t__ data; } ;
typedef  TYPE_1__ tftp_file_t ;
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 

ssize_t tftp_pread (tftp_file_t *F, void *buf, size_t count, off_t offset) {
  if (offset < 0 || offset > F->size) {
    return -1;
  }
  if (count > F->size - offset) {
    count = F->size - offset;
  }
  memcpy (buf, F->data + offset, count);
  return count;
}