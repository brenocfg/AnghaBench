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
 int /*<<< orphan*/  TL_BOOL_FALSE ; 
 int /*<<< orphan*/  TL_BOOL_TRUE ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tl_store_bool (int res) {
  if (res == 1) {
    tl_store_int (TL_BOOL_TRUE);
  } else {
    tl_store_int (TL_BOOL_FALSE);
  }
}