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
struct source {TYPE_1__* vtable; } ;
struct TYPE_4__ {size_t readsp; struct source* readstack; } ;
struct TYPE_3__ {int (* readchar ) (struct source*) ;} ;

/* Variables and functions */
 TYPE_2__ bmachine ; 
 int stub1 (struct source*) ; 

__attribute__((used)) static __inline int
readch(void)
{
	struct source *src = &bmachine.readstack[bmachine.readsp];

	return (src->vtable->readchar(src));
}