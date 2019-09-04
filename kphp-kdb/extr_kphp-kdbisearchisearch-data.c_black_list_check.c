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
 int /*<<< orphan*/ * aho_black_list ; 
 int trie_arr_check (int /*<<< orphan*/ *,char*) ; 

int black_list_check (char *s) {
  if (aho_black_list == NULL) {
    return 0;
  }
  return trie_arr_check (aho_black_list, s);
}