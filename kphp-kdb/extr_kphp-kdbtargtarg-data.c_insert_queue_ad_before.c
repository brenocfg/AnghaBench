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
struct advert {struct advert* prev; struct advert* next; } ;

/* Variables and functions */

inline void insert_queue_ad_before (struct advert *W, struct advert *A) {
  A->next = W;
  A->prev = W->prev;
  W->prev->next = A;
  W->prev = A;
}