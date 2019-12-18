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
typedef  int /*<<< orphan*/  search_query_heap_en_t ;

/* Variables and functions */
 int LAST_SEARCH_QUERY_BUFF_SIZE ; 
 int /*<<< orphan*/  copy_key ; 
 scalar_t__* last_search_query ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 int perform_query () ; 
 int /*<<< orphan*/  search_query_end (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_query_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int do_perform_query (const char *key, int len) {
  if (len < LAST_SEARCH_QUERY_BUFF_SIZE) {
    memcpy (last_search_query, key, len);
    last_search_query[len] = 0;
  } else {
    strcpy (last_search_query, "TOO LONG QUERY");
  }

  search_query_heap_en_t E;
  search_query_start (&E);
  int res = perform_query ();
  search_query_end (&E, res, (void *) key, copy_key);
  vkprintf (1, "perform_query result = %d\n", res);
  return res;
}