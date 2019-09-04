#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int message_id; int /*<<< orphan*/  hc; int /*<<< orphan*/  hashes; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ message_t ;
struct TYPE_4__ {int pos_to; int neg_to; int delmsg_cnt; int* delmsg_list; TYPE_1__* msgs; } ;

/* Variables and functions */
 int MAX_INTERMEDIATE_SIZE ; 
 int* Res ; 
 int* ResBuff ; 
 int ResL ; 
 int ResR ; 
 TYPE_2__* UH ; 
 int /*<<< orphan*/  assert (int*) ; 
 scalar_t__ cur_user ; 
 int /*<<< orphan*/  do_search (int,int,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  prefetch_search_lists () ; 
 scalar_t__ search_in_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int do_combined_search (void) {
  message_t *M;
  int prune_neg = 0, prune_pos = 0, first_neg = -0x7fffffff, first_pos = 0x7fffffff;
    
  ResL = 0;

  prefetch_search_lists();

  if (UH) {
    for (M = UH->msgs; M; M = M->prev) {
      if (M->message_id < 0 && M->message_id > first_neg) {
	first_neg = M->message_id;
      }
      if (M->message_id > 0 && M->message_id < first_pos) {
	first_pos = M->message_id;
      }
      if (search_in_msg (M->hashes, M->hc)) {
	ResBuff[ResL++] = M->message_id;
	if (ResL >= MAX_INTERMEDIATE_SIZE) {
	  return ResL;
	}
      }
    }
    prune_pos = UH->pos_to;
    prune_neg = UH->neg_to;
    if (verbosity > 0) {
      fprintf (stderr, "recent_search(): %d messages found\n", ResL);
    }
  }

  ResR = ResL;
  ResL = 0;
  if (cur_user > 0) {
    do_search (prune_pos, prune_neg, first_pos, first_neg);
  }

  ResL += ResR;
  Res = ResBuff;

  if (UH && UH->delmsg_cnt) {
    int *A = UH->delmsg_list, *B = A + UH->delmsg_cnt - 1;
    int i, j = 0, t;
    if (verbosity > 0) {
      fprintf (stderr, "user has %d deleted messages %d %d %d ..., pruning\n", UH->delmsg_cnt, A[0], A[1], A[2]);
    }
    assert (A);
    for (i = 0; i < ResL; i++) {
      t = ResBuff[i];
      if (t < 0) {
	while (A <= B && *A < t) { A++; }
	if (A <= B && *A == t) {
	  A++;
	} else {
	  ResBuff[j++] = t;
	}
      } else {
	while (A <= B && *B > t) { B--; }
	if (A <= B && *B == t) {
	  B--;
	} else {
	  ResBuff[j++] = t;
	}
      }
    }
    if (verbosity > 0) {
      fprintf (stderr, "pruned: resulting list contains %d, original %d\n", j, ResL);
    }
    ResL = j;
  }
  
  return ResL;
}