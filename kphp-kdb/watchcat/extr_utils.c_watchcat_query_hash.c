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
typedef  int /*<<< orphan*/  watchcat_query_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_watchcat_query (char*) ; 
 int /*<<< orphan*/  free_watchcat_query (int /*<<< orphan*/ *) ; 
 long long watchcat_query_hash_impl (int /*<<< orphan*/ *) ; 

long long watchcat_query_hash (char *s) {
  watchcat_query_t *query = create_watchcat_query (s);
  long long query_hash = watchcat_query_hash_impl (query);
  free_watchcat_query (query);
  return query_hash;
}