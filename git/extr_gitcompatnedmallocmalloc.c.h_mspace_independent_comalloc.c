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
typedef  int /*<<< orphan*/  mstate ;
typedef  int /*<<< orphan*/  mspace ;

/* Variables and functions */
 int /*<<< orphan*/  USAGE_ERROR_ACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** ialloc (int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  ok_magic (int /*<<< orphan*/ ) ; 

void** mspace_independent_comalloc(mspace msp, size_t n_elements,
				   size_t sizes[], void* chunks[]) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms,ms);
    return 0;
  }
  return ialloc(ms, n_elements, sizes, 0, chunks);
}