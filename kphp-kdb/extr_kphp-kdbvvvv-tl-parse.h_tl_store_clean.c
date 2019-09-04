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
struct TYPE_2__ {int /*<<< orphan*/  (* store_read_back ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TL_OUT ; 
 TYPE_1__* TL_OUT_METHODS ; 
 scalar_t__ TL_OUT_POS ; 
 int /*<<< orphan*/  TL_OUT_REMAINING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static inline int tl_store_clean (void) {
  assert (TL_OUT);
  TL_OUT_METHODS->store_read_back (TL_OUT_POS);
  TL_OUT_REMAINING += TL_OUT_POS;
  TL_OUT_POS = 0;
  return 0; 
}