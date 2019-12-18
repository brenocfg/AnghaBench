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
struct remote_binlog {int binlog_tag_len; char* binlog_tag; scalar_t__ flags; scalar_t__ first; } ;

/* Variables and functions */
 int HASH_PRIME ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 struct remote_binlog** rb_hash ; 
 void* zmalloc (int) ; 

struct remote_binlog *get_rb_hash (char *name, int l, int force) {
  int h1 = l, h2 = l, t;
  char *ptr;
  for (ptr = name, t = l; t--; ptr++) {
    if (*ptr >= 'A' && *ptr <= 'Z') {
      *ptr += 32;
    }
    h1 = (h1 * 239 + *ptr) % HASH_PRIME;
    h2 = (h2 * 17 + *ptr) % (HASH_PRIME - 1);
  }
  ++h2;
  while (rb_hash[h1]) {
    if (l == rb_hash[h1]->binlog_tag_len &&
        !memcmp (rb_hash[h1]->binlog_tag, name, l)) {
      return rb_hash[h1];
    }
    h1 += h2;
    if (h1 >= HASH_PRIME) {
      h1 -= HASH_PRIME;
    }
  }
  if (force) {
    char *temp = zmalloc (l + 1);
    memcpy (temp, name, l);
    temp[l] = 0;
    rb_hash[h1] = zmalloc (sizeof (struct remote_binlog));
    rb_hash[h1]->binlog_tag = temp;
    rb_hash[h1]->binlog_tag_len = l;
    rb_hash[h1]->first = 0;
    rb_hash[h1]->flags = 0;
    return rb_hash[h1];
  }
  return 0;
}