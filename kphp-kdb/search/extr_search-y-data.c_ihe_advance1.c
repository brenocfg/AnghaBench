#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item_t ;
struct TYPE_7__ {scalar_t__ doc_id; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cur1; TYPE_5__ Decoder; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 scalar_t__ IndexItems ; 
 scalar_t__ adv_ilist (TYPE_5__*) ; 
 int ihe_load (TYPE_1__*) ; 
 int ihe_load_I1_set (TYPE_1__*) ; 

__attribute__((used)) static int ihe_advance1 (iheap_en_t *A) {
  if (adv_ilist (&A->Decoder) >= 0) {
    A->cur1 = (item_t *) (IndexItems + A->Decoder.doc_id);
    return ihe_load_I1_set (A);
  }
  A->cur1 = NULL;
  return ihe_load (A);
}