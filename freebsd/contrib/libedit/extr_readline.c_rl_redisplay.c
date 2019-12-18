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
struct TYPE_4__ {scalar_t__** t_c; } ;
struct TYPE_5__ {TYPE_1__ el_tty; } ;

/* Variables and functions */
 size_t C_REPRINT ; 
 size_t TS_IO ; 
 TYPE_2__* e ; 
 int /*<<< orphan*/  el_push (TYPE_2__*,char*) ; 

void
rl_redisplay(void)
{
	char a[2];
	a[0] = (char)e->el_tty.t_c[TS_IO][C_REPRINT];
	a[1] = '\0';
	el_push(e, a);
}