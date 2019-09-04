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
struct counter {int created_at; struct counter* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_version (long long,int) ; 
 struct counter counter_wait ; 
 int /*<<< orphan*/  do_use (struct counter*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long long,int,int) ; 
 struct counter* get_counter_f (long long,int /*<<< orphan*/ ) ; 
 int load_counter (long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static struct counter *get_counter_old (long long cnt_id, int created_at, int use_aio) {
  if (verbosity >= 3) {
    fprintf (stderr, "get_counter_old (%lld, %d, %d)\n", cnt_id, created_at, use_aio);
  }

  if (use_aio > 0) {
    if (!check_version (cnt_id, created_at)) { return 0; }
    
    struct counter *D = get_counter_old (cnt_id, created_at, -1);
    if (D) { return D;}

  }


  struct counter *C = get_counter_f (cnt_id, 0);
  if (!C) { return C;}
  if (use_aio >= 0) {
    int res = load_counter (cnt_id, 0, use_aio);
    if (res == -1 && !C) {
      return 0;
    }
    if (res == -2) {
      return &counter_wait;
    }
  }
  if (!created_at) {
    do_use (C);
    return C;
  }


  while (C) {
    if (C->created_at < created_at) { 
      //if (use_aio) {
      //  assert (0);
      //}
      return 0; 
    }
    if (C->created_at == created_at) { break; }
    C = C->prev;
  }

  //if (use_aio == 1) {
  //  assert (C);
  //}

  if (C) { do_use (C); }
  return C;
}