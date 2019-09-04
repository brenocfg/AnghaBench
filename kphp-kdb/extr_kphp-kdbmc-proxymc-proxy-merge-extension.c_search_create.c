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
struct connection {int dummy; } ;

/* Variables and functions */
 int do_search_query (struct connection*,char*,int) ; 

int search_create (struct connection *c, char *key, int key_len) {
  return do_search_query (c, key, key_len);
}