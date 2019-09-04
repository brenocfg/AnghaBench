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
typedef  int /*<<< orphan*/  zval ;
struct tl_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** fetch_function (struct tl_tree*) ; 
 int /*<<< orphan*/  tl_parse_init () ; 
 int /*<<< orphan*/  tmp ; 

zval **vk_memcache_query_result_one (struct tl_tree *T) {
  tl_parse_init ();
  START_TIMER (tmp);
  zval **r = fetch_function (T);
  END_TIMER (tmp);
  return r;
}