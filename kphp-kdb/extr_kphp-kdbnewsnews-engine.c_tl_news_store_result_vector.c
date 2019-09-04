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
 int R ; 
 int R_end ; 
 int TL_VECTOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 
 int /*<<< orphan*/  tl_store_raw_data (void*,int) ; 

void tl_news_store_result_vector (int arity) {
  int num = R_end - R;
  assert (!(num % arity));
  tl_store_int (TL_VECTOR);
  tl_store_int (num / arity);
  tl_store_raw_data ( (void *) R, 4 * num);
}