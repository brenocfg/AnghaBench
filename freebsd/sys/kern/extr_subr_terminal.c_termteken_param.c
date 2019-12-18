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
struct terminal {TYPE_1__* tm_class; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc_param ) (struct terminal*,int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct terminal*,int,unsigned int) ; 

__attribute__((used)) static void
termteken_param(void *softc, int cmd, unsigned int arg)
{
	struct terminal *tm = softc;

	tm->tm_class->tc_param(tm, cmd, arg);
}