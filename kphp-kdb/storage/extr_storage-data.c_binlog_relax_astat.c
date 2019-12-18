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
struct TYPE_6__ {scalar_t__ fails; } ;
struct TYPE_5__ {double counter; scalar_t__ old_value; } ;
struct TYPE_7__ {TYPE_2__ st_read; TYPE_1__ as_read; } ;
typedef  TYPE_3__ storage_binlog_file_t ;

/* Variables and functions */

__attribute__((used)) static void binlog_relax_astat (storage_binlog_file_t *B, double e) {
  B->as_read.counter *= e;
  B->as_read.counter += B->st_read.fails - B->as_read.old_value;
  B->as_read.old_value = B->st_read.fails;
}