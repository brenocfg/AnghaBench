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
typedef  int /*<<< orphan*/  recommend_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  RECOMMEND_MODE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  items_kept ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void free_recommend_item (recommend_item_t *A) {
  assert (RECOMMEND_MODE);
  items_kept--;
  zfree (A, sizeof (*A));
}