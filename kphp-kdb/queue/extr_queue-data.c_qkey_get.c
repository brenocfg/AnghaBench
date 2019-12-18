#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* x; TYPE_2__* y; } ;
typedef  TYPE_1__ shmap_pair_string_vptr ;
struct TYPE_10__ {char* name; } ;
typedef  TYPE_2__ qkey ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dl_get_memory_used () ; 
 char* dl_strdup (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  h_qkey ; 
 TYPE_2__* qkey_malloc () ; 
 TYPE_1__* shmap_string_vptr_add (int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_1__* shmap_string_vptr_get (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  str_memory ; 
 int verbosity ; 

qkey *qkey_get (char *name, int force) {
  shmap_pair_string_vptr a, *b;
  a.y = NULL;
  a.x = name;

  qkey *k = NULL;
  if (force) {
    b = shmap_string_vptr_add (&h_qkey, a);
    if (b->y == NULL) {
      str_memory -= dl_get_memory_used();
      b->x = dl_strdup (b->x);
      str_memory += dl_get_memory_used();

      k = b->y = qkey_malloc();
      k->name = b->x;
    } else if (force == 1) {
      assert ("Keys collision" && 0);
    } else {
      k = b->y;
    }

    if (verbosity > 2) {
      fprintf (stderr, "Key created : [%s]\n", name);
    }
    // dbg ("Key created %p : [%s]:%p\n", k, k->name, k->name);
  } else {
//    fprintf (stderr, "get Key %p : ", name);
//    fprintf (stderr, "[%s]\n", name);
    b = shmap_string_vptr_get (&h_qkey, a);
    if (b != NULL) {
      k = b->y;
    }
  }

  return k;
}