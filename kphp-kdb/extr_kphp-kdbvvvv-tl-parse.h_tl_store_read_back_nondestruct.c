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
struct TYPE_2__ {int /*<<< orphan*/  (* store_read_back_nondestruct ) (char*,int) ;} ;

/* Variables and functions */
 TYPE_1__* TL_OUT_METHODS ; 
 int TL_OUT_POS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 

__attribute__((used)) static inline int tl_store_read_back_nondestruct (char *buf, int size) {
  assert (size <= TL_OUT_POS);
  TL_OUT_METHODS->store_read_back_nondestruct (buf, size);
  return size;
}