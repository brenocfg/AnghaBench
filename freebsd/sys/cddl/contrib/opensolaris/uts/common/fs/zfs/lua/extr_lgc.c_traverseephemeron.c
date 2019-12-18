#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ gcstate; int /*<<< orphan*/  grayagain; int /*<<< orphan*/  allweak; int /*<<< orphan*/  ephemeron; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_11__ {int sizearray; int /*<<< orphan*/ * array; } ;
typedef  TYPE_2__ Table ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 int /*<<< orphan*/  checkdeadkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnodelast (TYPE_2__*) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ *) ; 
 scalar_t__ iscleared (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linktable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reallymarkobject (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removeentry (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ valiswhite (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int traverseephemeron (global_State *g, Table *h) {
  int marked = 0;  /* true if an object is marked in this traversal */
  int hasclears = 0;  /* true if table has white keys */
  int prop = 0;  /* true if table has entry "white-key -> white-value" */
  Node *n, *limit = gnodelast(h);
  int i;
  /* traverse array part (numeric keys are 'strong') */
  for (i = 0; i < h->sizearray; i++) {
    if (valiswhite(&h->array[i])) {
      marked = 1;
      reallymarkobject(g, gcvalue(&h->array[i]));
    }
  }
  /* traverse hash part */
  for (n = gnode(h, 0); n < limit; n++) {
    checkdeadkey(n);
    if (ttisnil(gval(n)))  /* entry is empty? */
      removeentry(n);  /* remove it */
    else if (iscleared(g, gkey(n))) {  /* key is not marked (yet)? */
      hasclears = 1;  /* table must be cleared */
      if (valiswhite(gval(n)))  /* value not marked yet? */
        prop = 1;  /* must propagate again */
    }
    else if (valiswhite(gval(n))) {  /* value not marked yet? */
      marked = 1;
      reallymarkobject(g, gcvalue(gval(n)));  /* mark it now */
    }
  }
  if (g->gcstate != GCSatomic || prop)
    linktable(h, &g->ephemeron);  /* have to propagate again */
  else if (hasclears)  /* does table have white keys? */
    linktable(h, &g->allweak);  /* may have to clean white keys */
  else  /* no white keys */
    linktable(h, &g->grayagain);  /* no need to clean */
  return marked;
}