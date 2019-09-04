#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct advert {TYPE_1__* prev; TYPE_1__* next; } ;
struct TYPE_2__ {struct TYPE_2__* next; struct TYPE_2__* prev; } ;

/* Variables and functions */

inline void remove_queue_ad (struct advert *A) {
  if (A->next) {
    A->next->prev = A->prev;
    A->prev->next = A->next;
    A->next = A->prev = 0;
  }
}