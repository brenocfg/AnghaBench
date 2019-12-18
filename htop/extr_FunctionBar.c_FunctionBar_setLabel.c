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
struct TYPE_3__ {int size; int* events; int /*<<< orphan*/ * functions; } ;
typedef  TYPE_1__ FunctionBar ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xStrdup (char const*) ; 

void FunctionBar_setLabel(FunctionBar* this, int event, const char* text) {
   for (int i = 0; i < this->size; i++) {
      if (this->events[i] == event) {
         free(this->functions[i]);
         this->functions[i] = xStrdup(text);
         break;
      }
   }
}