#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cur; scalar_t__ cur1; scalar_t__ cur0; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ihe_advance0 (TYPE_1__*) ; 
 int ihe_advance1 (TYPE_1__*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int ihe_advance (iheap_en_t *A) {
  assert (A->cur);
  if (likely (A->cur == A->cur1)) { return ihe_advance1 (A); }
  assert (A->cur == A->cur0);
  return ihe_advance0 (A);
}