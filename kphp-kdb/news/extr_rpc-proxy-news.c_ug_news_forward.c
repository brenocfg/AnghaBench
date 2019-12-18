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
 int TL_NEWS_GET_GROUPED_UPDATES ; 
 int TL_NEWS_GET_RAW_UPDATES ; 
 int default_firstint_forward () ; 
 int /*<<< orphan*/  merge_forward (int /*<<< orphan*/ *) ; 
 int tl_fetch_lookup_int () ; 
 int /*<<< orphan*/  ugnews_gather_methods ; 
 int /*<<< orphan*/  ugnews_raw_gather_methods ; 

int ug_news_forward (void) {
  int op = tl_fetch_lookup_int ();
  if (op == TL_NEWS_GET_GROUPED_UPDATES) {
    merge_forward (&ugnews_gather_methods);
    return 0;
  } else if (op == TL_NEWS_GET_RAW_UPDATES) {
    merge_forward (&ugnews_raw_gather_methods);
    return 0;
  } else {
    return default_firstint_forward ();
  }
}