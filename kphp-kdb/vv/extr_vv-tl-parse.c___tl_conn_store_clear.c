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

/* Variables and functions */
 scalar_t__ TL_OUT ; 
 scalar_t__ TL_OUT_POS ; 
 int /*<<< orphan*/  __tl_conn_store_read_back (scalar_t__) ; 

__attribute__((used)) static inline void __tl_conn_store_clear (void) {
  if (TL_OUT) {
    __tl_conn_store_read_back (TL_OUT_POS + 20);
  }
}