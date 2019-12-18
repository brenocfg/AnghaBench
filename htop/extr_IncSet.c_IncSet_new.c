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
struct TYPE_4__ {int filtering; int /*<<< orphan*/ * defaultBar; int /*<<< orphan*/ * active; int /*<<< orphan*/ * modes; } ;
typedef  TYPE_1__ IncSet ;
typedef  int /*<<< orphan*/  FunctionBar ;

/* Variables and functions */
 size_t INC_FILTER ; 
 size_t INC_SEARCH ; 
 int /*<<< orphan*/  IncMode_initFilter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IncMode_initSearch (int /*<<< orphan*/ *) ; 
 TYPE_1__* xCalloc (int,int) ; 

IncSet* IncSet_new(FunctionBar* bar) {
   IncSet* this = xCalloc(1, sizeof(IncSet));
   IncMode_initSearch(&(this->modes[INC_SEARCH]));
   IncMode_initFilter(&(this->modes[INC_FILTER]));
   this->active = NULL;
   this->filtering = false;
   this->defaultBar = bar;
   return this;
}