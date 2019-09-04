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
struct TYPE_2__ {size_t trim_threshold; size_t page_size; size_t granularity; size_t mmap_threshold; } ;

/* Variables and functions */
 size_t MAX_SIZE_T ; 
#define  M_GRANULARITY 130 
#define  M_MMAP_THRESHOLD 129 
#define  M_TRIM_THRESHOLD 128 
 int /*<<< orphan*/  ensure_initialization () ; 
 TYPE_1__ mparams ; 

__attribute__((used)) static int change_mparam(int param_number, int value) {
  size_t val = (value == -1)? MAX_SIZE_T : (size_t)value;
  ensure_initialization();
  switch(param_number) {
  case M_TRIM_THRESHOLD:
    mparams.trim_threshold = val;
    return 1;
  case M_GRANULARITY:
    if (val >= mparams.page_size && ((val & (val-1)) == 0)) {
      mparams.granularity = val;
      return 1;
    }
    else
      return 0;
  case M_MMAP_THRESHOLD:
    mparams.mmap_threshold = val;
    return 1;
  default:
    return 0;
  }
}