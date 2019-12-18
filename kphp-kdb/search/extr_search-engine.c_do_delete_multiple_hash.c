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
struct hashset_ll {int filled; } ;
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int delete_hash_query_items ; 
 int do_delete_items_with_hash_using_hashset (struct hashset_ll*) ; 
 int /*<<< orphan*/  hashset_ll_free (struct hashset_ll*) ; 
 int /*<<< orphan*/  hashset_ll_init (struct hashset_ll*,int) ; 
 int /*<<< orphan*/  hashset_ll_insert (struct hashset_ll*,long long) ; 
 int read_in (int /*<<< orphan*/ *,char*,int) ; 
 int sscanf (char*,char*,long long*) ; 
 char* strchr (char*,char) ; 
 char* value_buff ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long) ; 

int do_delete_multiple_hash (struct connection *c, int size) {
  char *a = value_buff;
  assert (read_in (&c->In, a, size) == size);
  a[size] = 0;
  int i, n = 1;
  for (i = 0; i < size; i++) {
    if (a[i] == ',') {
      n++;
    }
  }
  if (n < 10) {
    n = 10;
  }
  struct hashset_ll H;
  if (!hashset_ll_init (&H, n)) {
    return 0;
  }
  char *p = a;
  while (*p) {
    char *q = strchr (p, ',');
    if (q != NULL) {
      *q = 0;
    }
    long long u;
    if (sscanf (p, "%llx", &u) != 1) {
      break;
    }
    if (H.filled >= n) { break; }
    vkprintf (3, "u = %llx\n", u);
    if (u) {
      hashset_ll_insert (&H, u);
    }
    if (q == NULL) {
      break;
    }
    p = q + 1;
  }
  int t = do_delete_items_with_hash_using_hashset (&H);
  delete_hash_query_items += t;
  hashset_ll_free (&H);
  return 1;
}