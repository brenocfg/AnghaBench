#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wkey ;
typedef  int /*<<< orphan*/  watchcat_query_t ;
struct TYPE_4__ {int /*<<< orphan*/  keys; } ;
typedef  TYPE_1__ watchcat ;

/* Variables and functions */
 int /*<<< orphan*/ * create_watchcat_query (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long long,char*,int,int) ; 
 int /*<<< orphan*/  free_watchcat_query (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_watchcat (long long,int /*<<< orphan*/ *) ; 
 int my_verbosity ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * trp_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int watchcat_query_hash_impl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wkey_fix (int /*<<< orphan*/ *,int) ; 

void subscribe_watchcat (long long id, char *s, int q_id, int timeout) {
  if (my_verbosity > 1) {
    fprintf (stderr, "subscribe wathcat %lld (%s), q_id = %d, timeout = %d\n", id, s, q_id, timeout);
  }


  watchcat_query_t *query = create_watchcat_query (s);
  if (watchcat_query_hash_impl (query) == -1) {
    free_watchcat_query (query);
    return;
  }
  watchcat *w = get_watchcat (id, query);

  wkey *k = trp_add (&w->keys, q_id, rand(), w);
  wkey_fix (k, timeout);
}