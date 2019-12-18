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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int data_get_cnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * user_get_album_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 

int user_get_albums_count (user *u) {
//  dbg ("user_get_albums_count %d\n", u->id);

  assert (user_loaded (u));
  data *d = user_get_album_data (u);

  return data_get_cnt (d);
}