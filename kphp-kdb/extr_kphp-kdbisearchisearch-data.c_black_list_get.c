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
 int /*<<< orphan*/  black_list ; 
 scalar_t__ buff ; 
 char* buff2 ; 
 int /*<<< orphan*/  trie_arr_text_save (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  trie_encode (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

char *black_list_get (void) {
  trie_encode (black_list, buff, 0);
  int len = 0;
  trie_arr_text_save ((trie_arr_node *)buff, buff2, &len);
  if (len) {
    len--;
  }

  buff2[len] = 0;
  return buff2;
}