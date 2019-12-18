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
struct TYPE_3__ {int /*<<< orphan*/  c_keytype; int /*<<< orphan*/  c_output_name; int /*<<< orphan*/  c_namelist; } ;
typedef  TYPE_1__ con ;

/* Variables and functions */
 int conalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  confree (int) ; 
 TYPE_1__* fdcon ; 

__attribute__((used)) static int
conrecycle(int s)
{
	con *c = &fdcon[s];
	int ret;

	ret = conalloc(c->c_namelist, c->c_output_name, c->c_keytype);
	confree(s);
	return (ret);
}