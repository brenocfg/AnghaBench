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
struct TYPE_3__ {void* lessData; int /*<<< orphan*/  lessFunc; } ;
typedef  TYPE_1__ UniqueIndices ;
typedef  int /*<<< orphan*/  LessFunc ;

/* Variables and functions */

void UniqueIndices_init(UniqueIndices* self, LessFunc lessFunc, void* lessData) {
	self->lessFunc = lessFunc;
	self->lessData = lessData;
}