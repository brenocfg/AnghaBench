#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_3__ {int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ ptrmetric; } ;

/* Variables and functions */
 TYPE_2__* IR ; 
 int /*<<< orphan*/  POINTER ; 
 int /*<<< orphan*/  pointersym ; 
 int /*<<< orphan*/  type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Type ptr(Type ty) {
	return type(POINTER, ty, IR->ptrmetric.size,
		IR->ptrmetric.align, pointersym);
}