#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item_t ;
struct TYPE_13__ {scalar_t__ doc_id; } ;
struct TYPE_12__ {int* Bt; int sp; TYPE_5__** TS; int /*<<< orphan*/  cur0; TYPE_4__ Decoder; int /*<<< orphan*/ * cur1; int /*<<< orphan*/  word; } ;
typedef  TYPE_1__ iheap_en_t ;
typedef  int /*<<< orphan*/  hash_t ;
struct TYPE_14__ {int /*<<< orphan*/  item; } ;

/* Variables and functions */
 scalar_t__ IndexItems ; 
 TYPE_5__* Root ; 
 scalar_t__ adv_ilist (TYPE_4__*) ; 
 int ihe_dive (TYPE_1__*) ; 
 int ihe_load (TYPE_1__*) ; 
 int ihe_sgn (TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ init_ilist_decoder (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ihe_init (iheap_en_t *A) {
  const hash_t word = A->word;
  int sgn, sp;
  memset (A, 0, sizeof (*A));

  //commented useless code: after memset
  //A->sp = 0;
  //A->cur = A->cur0 = A->cur1 = 0;

  A->word = word;
  A->TS[0] = Root;
  A->Bt[0] = -1;

  if (init_ilist_decoder (A, &A->Decoder, word)) {
    if (adv_ilist (&A->Decoder) >= 0) {
      A->cur1 = (item_t *) (IndexItems + A->Decoder.doc_id);
    }
  }

  if (!Root) {
    sgn = 1;
  } else {
    sgn = ihe_dive (A);
    sp = A->sp;

    if (sgn < 0 && A->Bt[sp] >= 0) {
      sp = A->Bt[sp];
      sgn = ihe_sgn (A->TS[sp], A);
    }
  }

  if (sgn != 0) {
    A->sp = -1;
    A->cur0 = 0;
    return ihe_load (A);
  }

  A->sp = sp;
  A->cur0 = A->TS[sp]->item;
  //  A->cur_y = A->TS[sp]->y;

  return ihe_load (A);
}