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
struct TYPE_5__ {scalar_t__ cur; scalar_t__ cur0; scalar_t__ cur1; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int ihe_advance0 (TYPE_1__*) ; 
 int ihe_advance1 (TYPE_1__*) ; 

__attribute__((used)) static int ihe_advance (iheap_en_t *A) {
  if (!A->cur) { return 0; }
  if (A->cur == A->cur0) { return ihe_advance0 (A); }
  else if (A->cur == A->cur1) { return ihe_advance1 (A); }
  else assert (0);
  return 0;
}