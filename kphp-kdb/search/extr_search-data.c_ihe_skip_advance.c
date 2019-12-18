#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* ihe_skip_advance1 ) (TYPE_1__*,long long) ;scalar_t__ cur1; scalar_t__ cur0; } ;
typedef  TYPE_1__ iheap_en_t ;

/* Variables and functions */
 int ihe_load (TYPE_1__*) ; 
 int /*<<< orphan*/  ihe_skip_advance0 (TYPE_1__*,long long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,long long) ; 

__attribute__((used)) inline static int ihe_skip_advance (iheap_en_t *A, long long item_id) {
  if (A->cur0) {
    ihe_skip_advance0 (A, item_id);
  }
  if (A->cur1) {
    A->ihe_skip_advance1 (A, item_id);
  }
  return ihe_load (A);
}