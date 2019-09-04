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
 int MASK_IMPORTANT_TRANSACTION ; 
 int MASK_RERUN_TRANSACTION ; 
 int MASK_WAITING_TRANSACTION ; 

int check_mask (int mask) {
  return ((mask & (MASK_RERUN_TRANSACTION | MASK_IMPORTANT_TRANSACTION | MASK_WAITING_TRANSACTION)) == 0);
}