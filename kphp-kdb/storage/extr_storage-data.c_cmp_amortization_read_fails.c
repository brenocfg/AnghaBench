#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ counter; } ;
struct TYPE_7__ {TYPE_1__ as_read; } ;
typedef  TYPE_2__ storage_binlog_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  NEXT ; 
 double fabs (scalar_t__) ; 

__attribute__((used)) static storage_binlog_file_t *cmp_amortization_read_fails (void **IP, storage_binlog_file_t *A, storage_binlog_file_t *B) {
  if (fabs (A->as_read.counter - B->as_read.counter) < 1.0) {
    NEXT;
  }
  return A->as_read.counter < B->as_read.counter ? A : B;
}