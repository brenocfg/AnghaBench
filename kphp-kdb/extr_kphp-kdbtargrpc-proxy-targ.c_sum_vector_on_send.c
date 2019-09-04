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
struct targ_extra {int op; int mode; int limit; int ad_id; } ;
struct gather {struct targ_extra* extra; } ;

/* Variables and functions */
#define  TL_TARG_RECENT_AD_VIEWERS 129 
#define  TL_TARG_RECENT_VIEWS_STATS 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_store_int (int) ; 

int sum_vector_on_send (struct gather *G, int num) {
  struct targ_extra *e = G->extra;
  switch (e->op) {
  case TL_TARG_RECENT_VIEWS_STATS:
    tl_store_int (e->op);
    tl_store_int (e->mode & (~1));
    tl_store_int (e->limit + 100);
    break;
  case TL_TARG_RECENT_AD_VIEWERS:
    tl_store_int (e->op);
    tl_store_int (e->ad_id);
    tl_store_int (e->mode & (~1));
    tl_store_int (e->limit);
    break;
  default:
    fprintf (stderr, "op = 0x%08x\n", e->op);
    assert (0);
  }
  return 0;
}