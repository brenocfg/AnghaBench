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
typedef  int /*<<< orphan*/  listree_t ;

/* Variables and functions */
 int account_date (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metafile_get_date (int) ; 

__attribute__((used)) static inline int barray_account_date (listree_t *LT, int temp_id) {
  return account_date (metafile_get_date (temp_id));
}