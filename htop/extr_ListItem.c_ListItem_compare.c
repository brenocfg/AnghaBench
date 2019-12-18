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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ListItem ;

/* Variables and functions */
 long strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

long ListItem_compare(const void* cast1, const void* cast2) {
   ListItem* obj1 = (ListItem*) cast1;
   ListItem* obj2 = (ListItem*) cast2;
   return strcmp(obj1->value, obj2->value);
}