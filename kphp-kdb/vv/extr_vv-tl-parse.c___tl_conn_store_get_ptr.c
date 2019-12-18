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
struct TYPE_2__ {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 TYPE_1__* TL_OUT_CONN ; 
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,int) ; 
 void* get_write_ptr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void *__tl_conn_store_get_ptr (int len) {
  void *r = get_write_ptr (&TL_OUT_CONN->Out, len);
  advance_write_ptr (&TL_OUT_CONN->Out, len);
  return r;
}