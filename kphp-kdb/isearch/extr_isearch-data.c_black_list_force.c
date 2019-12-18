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
typedef  int /*<<< orphan*/  trie_arr_node ;

/* Variables and functions */
 int /*<<< orphan*/  aho_black_list ; 
 int /*<<< orphan*/  aho_black_list_size ; 
 int /*<<< orphan*/  black_list ; 
 scalar_t__ buff ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_arr_aho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trie_encode (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void black_list_force (void) {
  dl_free (aho_black_list, aho_black_list_size);

  aho_black_list_size = trie_encode (black_list, buff, 0);
  trie_arr_aho ((trie_arr_node *)buff);
  aho_black_list = dl_malloc (aho_black_list_size);
  memcpy (aho_black_list, buff, aho_black_list_size);
}