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
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/  predicate ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RESULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int data_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int data_slice_filtered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  result_obj ; 
 int /*<<< orphan*/ * user_get_photo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 

int user_get_photos_count_pred (user *u, int aid, predicate *pred) {
//  dbg ("user_get_photos_count_pred %d: album_id = %d\n", u->id, aid);

  assert (user_loaded (u));
  data *d = user_get_photo_data (u, aid);
  if (d == NULL) {
    return -1;
  }

  if (pred == NULL) {
    return data_slice (d, result_obj, MAX_RESULT, 0);
  } else {
    return data_slice_filtered (d, result_obj, MAX_RESULT, 0, pred);
  }
}