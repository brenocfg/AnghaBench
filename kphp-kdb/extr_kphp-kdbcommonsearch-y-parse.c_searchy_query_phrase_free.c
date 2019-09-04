#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ searchy_query_phrase_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

void searchy_query_phrase_free (searchy_query_phrase_t *P) {
  while (P) {
    searchy_query_phrase_t *W = P->next;
    zfree (P, sizeof (*P));
    P = W;
  }
}