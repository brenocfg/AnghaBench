#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  defaultBar; TYPE_1__* active; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  bar; } ;
typedef  TYPE_2__ IncSet ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void IncSet_drawBar(IncSet* this) {
   if (this->active) {
      FunctionBar_draw(this->active->bar, this->active->buffer);
   } else {
      FunctionBar_draw(this->defaultBar, NULL);
   }
}