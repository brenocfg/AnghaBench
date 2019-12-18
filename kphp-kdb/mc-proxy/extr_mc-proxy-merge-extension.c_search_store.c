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
 int merge_store (struct connection*,int,char const*,int,int,int,int) ; 

int search_store (struct connection *c, int op, const char *key, int key_len, int expire, int flags, int bytes) {
  return merge_store (c, op, key, key_len, expire, flags, bytes);
}