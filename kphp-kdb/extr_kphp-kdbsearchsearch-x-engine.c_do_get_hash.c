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
 scalar_t__ get_hash (long long*,long long) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 int sprintf (char*,char*,long long) ; 
 int sscanf (char const*,char*,int*,...) ; 

__attribute__((used)) static int do_get_hash (struct connection *c, const char *key, int len, int dog_len) {
  int owner_id, short_id, op = 0;
  long long item_id;
  static char value[32];
  if (sscanf (key, "hash%d_%d ", &owner_id, &short_id) == 2) {
    if (owner_id && short_id > 0) {
      item_id = (((long long) short_id) << 32) + (unsigned) owner_id;
      op = 1;
    }
  } else if (sscanf (key, "hash%d ", &short_id) == 1) {
    if (short_id > 0) {
      item_id = short_id;
      op = 1;
    }
  }
  if (op) {
    long long hash;
    if (get_hash (&hash, item_id)) {
      if (hash == 0) { return return_one_key (c, key - dog_len, "0", 1); }
      else { return return_one_key (c, key - dog_len, value, sprintf (value, "%016llx", hash)); }
    }
  }
  return 0;
}