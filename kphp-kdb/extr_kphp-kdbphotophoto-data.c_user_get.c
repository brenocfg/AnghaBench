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
typedef  int /*<<< orphan*/  predicate ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int MAX_RESULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int data_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int data_slice_filtered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  result_obj ; 

inline int user_get (data *d, int n, int offset, predicate *pred) {
  assert (d != NULL);
  if (n > MAX_RESULT) {
    n = MAX_RESULT;
  }

  if (pred == NULL) {
    return data_slice (d, result_obj, n, offset);
  } else {
    return data_slice_filtered (d, result_obj, n, offset, pred);
  }
}