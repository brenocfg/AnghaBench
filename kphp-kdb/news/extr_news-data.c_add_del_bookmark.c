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
 int /*<<< orphan*/  PACK_BOOKMARK (long long,int,int,int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  insert_bookmark (int,long long,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int add_del_bookmark (int user_id, int type, int owner, int place, int y) {
  if (verbosity > 2) {
    fprintf (stderr, "add_del_bookmark: %d - %d - %d\n", type, owner, place);
  }
  if (!check_obj (type, owner, place) || user_id <= 0) {
    return 0;
  }
  long long t;
  PACK_BOOKMARK (t, type, owner, place);
  insert_bookmark (user_id, t, y, 1);
  return 1;
}