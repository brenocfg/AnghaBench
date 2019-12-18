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
struct TYPE_2__ {int /*<<< orphan*/  (* fetch_lookup ) (int*,int) ;} ;

/* Variables and functions */
 TYPE_1__* TL_IN_METHODS ; 
 int /*<<< orphan*/  stub1 (int*,int) ; 
 scalar_t__ tl_fetch_check (int) ; 

__attribute__((used)) static inline int tl_fetch_lookup_int (void) {
  if (tl_fetch_check (4) < 0) {
    return -1;
  }
  int x;
  TL_IN_METHODS->fetch_lookup (&x, 4);
  return x;
}