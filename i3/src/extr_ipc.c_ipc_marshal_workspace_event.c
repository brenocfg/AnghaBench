#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  yajl_gen ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  null ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ygenalloc () ; 
 int /*<<< orphan*/  ystr (char const*) ; 

yajl_gen ipc_marshal_workspace_event(const char *change, Con *current, Con *old) {
    setlocale(LC_NUMERIC, "C");
    yajl_gen gen = ygenalloc();

    y(map_open);

    ystr("change");
    ystr(change);

    ystr("current");
    if (current == NULL)
        y(null);
    else
        dump_node(gen, current, false);

    ystr("old");
    if (old == NULL)
        y(null);
    else
        dump_node(gen, old, false);

    y(map_close);

    setlocale(LC_NUMERIC, "");

    return gen;
}