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
 int MAX_RESULT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int user_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * user_get_album_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 

int user_get_albums (user *u, int offset, int limit, predicate *pred) {
  assert (user_loaded (u));

  if (offset < 0) {
    offset = 0;
  }

  if (offset > MAX_RESULT) {
    offset = MAX_RESULT;
  }

  if (limit <= 0) {
    return 0;
  }

  if (limit > MAX_RESULT) {
    limit = MAX_RESULT;
  }

  data *d = user_get_album_data (u);
  return user_get (d, limit, offset, pred);
}