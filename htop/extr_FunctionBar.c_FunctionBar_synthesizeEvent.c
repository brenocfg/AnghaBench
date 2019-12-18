#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int* events; int /*<<< orphan*/ * functions; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ FunctionBar ;

/* Variables and functions */
 int ERR ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int FunctionBar_synthesizeEvent(const FunctionBar* this, int pos) {
   int x = 0;
   for (int i = 0; i < this->size; i++) {
      x += strlen(this->keys[i]);
      x += strlen(this->functions[i]);
      if (pos < x) {
         return this->events[i];
      }
   }
   return ERR;
}