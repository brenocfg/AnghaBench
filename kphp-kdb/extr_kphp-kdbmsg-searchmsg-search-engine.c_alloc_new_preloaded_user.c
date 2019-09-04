#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; char* ptr; int size; int user_id; void* lru; } ;
typedef  TYPE_1__ loaded_user_t ;

/* Variables and functions */
 TYPE_1__* LoadedUsers ; 
 int MAX_LOADED_USERS ; 
 int MAX_USER_DATA ; 
 int USER_DATA_BUFF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int loaded_users_cnt ; 
 void* loaded_users_lru ; 
 int loaded_users_max ; 
 int loaded_users_size ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* udata ; 
 scalar_t__ verbosity ; 

loaded_user_t *alloc_new_preloaded_user (int user_id, int size) {
  int i, j;
  char *prev, *cur;
  loaded_user_t *U;

  assert (size > 0);
  size = (size + 15) & -16;
  if (size >= MAX_USER_DATA) return 0;

  do {

    prev = udata + ((16 - (long) udata) & 15);
    j = -1;

    for (i = 0, U = LoadedUsers; i < loaded_users_max; i++, U++) {
      if (U->state > 0) {
	cur = U->ptr;
	if (verbosity > 0) {
	  fprintf (stderr, "skipping occupied slot #%d at %p, size %d for user %d [prev=%p]\n",
		   i, cur, U->size, U->user_id, prev);
	}
	assert (cur >= prev);
	if (cur >= prev + size) {
	  if (verbosity > 0) {
	    fprintf (stderr, "allocating slot #%d at %p, size %d for user %d\n",
		     j, prev, size, user_id);
	  }
	  assert (j >= 0);
	  U = LoadedUsers + j;
	  loaded_users_cnt++;
	  memset (U, 0, sizeof(loaded_user_t));
	  U->state = 1;
	  U->user_id = user_id;
	  U->ptr = prev;
	  U->size = size;
	  loaded_users_size += size;
	  U->lru = ++loaded_users_lru;
	  return U;
	}
	prev = cur + U->size;
	j = -1;
      } else if (j < 0) {
	j = i;
      }
    }
    if (j < 0) {
      j = loaded_users_max;
    }
    if (j < MAX_LOADED_USERS && prev + size <= udata + USER_DATA_BUFF) {
      if (j == loaded_users_max) {
	loaded_users_max++;
      }
      if (verbosity > 0) {
	fprintf (stderr, "allocating new slot #%d (out of %d) at %p, size %d for user %d\n",
		 j, loaded_users_max, prev, size, user_id);
      }
      U = LoadedUsers + j;
      loaded_users_cnt++;
      memset (U, 0, sizeof(loaded_user_t));
      U->state = 1;
      U->user_id = user_id;
      U->ptr = prev;
      U->size = size;
      loaded_users_size += size;
      U->lru = ++loaded_users_lru;
      return U;
    }
    /* HACK - DROP ALL CACHE IF ALLOCATION FAILS */
    // drop_lru_user();
    if (!loaded_users_cnt) { break; }
    loaded_users_max = loaded_users_cnt = loaded_users_size = 0;

  } while (1);

  return 0;
}