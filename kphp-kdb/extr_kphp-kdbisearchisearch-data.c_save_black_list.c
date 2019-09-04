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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  black_list ; 
 scalar_t__ buff ; 
 int /*<<< orphan*/  buff2 ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  trie_arr_aho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trie_arr_text_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  trie_encode (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int save_black_list (void) {
  // TODO: fix to trie_save_text
  trie_encode (black_list, buff, 0);
  int len = 0;
  trie_arr_text_save ((trie_arr_node *)buff, buff2, &len);
  trie_arr_aho ((trie_arr_node *)buff);

  assert (write (fd[1], buff2, len) == len);

  //fprintf (stderr, "black_list_write = %d <%s>\n", len, buff2);
  return len;
}