#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct item {int dummy; } ;
struct TYPE_6__ {scalar_t__ doc_id; } ;
struct TYPE_5__ {struct item* cur1; TYPE_4__ Decoder; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 scalar_t__ IndexItems ; 
 scalar_t__ adv_ilist (TYPE_4__*) ; 
 int ihe_load (TYPE_1__*) ; 

__attribute__((used)) static int ihe_advance1 (iheap_en_t *A) {
  if (adv_ilist (&A->Decoder) >= 0) {
    A->cur1 = (struct item *) (IndexItems + A->Decoder.doc_id);
  } else {
    A->cur1 = 0;
  }
  return ihe_load (A);
}