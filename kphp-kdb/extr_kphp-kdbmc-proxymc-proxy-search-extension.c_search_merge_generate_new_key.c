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
 int generate_new_key (char*,char*,int,int) ; 
 int prepare_search_query (char*,int) ; 

int search_merge_generate_new_key (char *buff, char *key, int key_len, void *E) {
  int i = prepare_search_query (key, key_len);
  return generate_new_key (buff, key, key_len, i);
}