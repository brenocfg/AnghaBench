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
struct console {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* c_probe ) (struct console*) ;} ;

/* Variables and functions */
 TYPE_1__** consoles ; 
 TYPE_1__* parent ; 
 int /*<<< orphan*/  stub1 (struct console*) ; 

__attribute__((used)) static void
spinc_probe(struct console *cp)
{

	if (parent == NULL)
		parent = consoles[0];
	parent->c_probe(cp);
}