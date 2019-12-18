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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {scalar_t__ pos; int /*<<< orphan*/ * buf; } ;
struct TYPE_4__ {TYPE_1__ string; } ;
struct source {int /*<<< orphan*/ * vtable; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_vtable ; 

void
src_setstring(struct source *src, char *p)
{

	src->u.string.buf = (u_char *)p;
	src->u.string.pos = 0;
	src->vtable = &string_vtable;
}