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
typedef  int /*<<< orphan*/  yajl_gen ;
struct TYPE_3__ {int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  inner; } ;
typedef  TYPE_1__ gaps_t ;

/* Variables and functions */
 int /*<<< orphan*/  integer ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ystr (char const*) ; 

__attribute__((used)) static void dump_gaps(yajl_gen gen, const char *name, gaps_t gaps) {
    ystr(name);
    y(map_open);
    ystr("inner");
    y(integer, gaps.inner);

    // TODO: the i3ipc Python modules recognize gaps, but only inner/outer
    // This is currently here to preserve compatibility with that
    ystr("outer");
    y(integer, gaps.top);

    ystr("top");
    y(integer, gaps.top);
    ystr("right");
    y(integer, gaps.right);
    ystr("bottom");
    y(integer, gaps.bottom);
    ystr("left");
    y(integer, gaps.left);
    y(map_close);
}