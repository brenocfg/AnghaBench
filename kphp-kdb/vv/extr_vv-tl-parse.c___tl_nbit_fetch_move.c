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
 int /*<<< orphan*/  TL_IN_NBIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int nbit_advance (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void __tl_nbit_fetch_move (int len) {
  assert (nbit_advance (TL_IN_NBIT, len) == len);
}