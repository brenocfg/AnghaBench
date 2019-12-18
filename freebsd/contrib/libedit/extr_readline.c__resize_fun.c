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
struct TYPE_3__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ LineInfo ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 TYPE_1__* el_line (int /*<<< orphan*/ *) ; 
 char* memchr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
_resize_fun(EditLine *el, void *a)
{
	const LineInfo *li;
	char **ap = a;

	li = el_line(el);
	/* a cheesy way to get rid of const cast. */
	*ap = memchr(li->buffer, *li->buffer, (size_t)1);
}