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
typedef  int /*<<< orphan*/  netbuffer_t ;
struct TYPE_4__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ nb_iterator_t ;

/* Variables and functions */
 int nbit_rewind (TYPE_1__*) ; 

int nbit_set (nb_iterator_t *I, netbuffer_t *H) {
  I->head = H;
  return nbit_rewind (I);
}