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
struct termp {scalar_t__ ti; TYPE_1__* tcol; int /*<<< orphan*/  line; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  putwchar (int) ; 

__attribute__((used)) static void
locale_endline(struct termp *p)
{

	p->line++;
	p->tcol->offset -= p->ti;
	p->ti = 0;
	putwchar(L'\n');
}