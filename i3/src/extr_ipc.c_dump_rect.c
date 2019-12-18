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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ Rect ;

/* Variables and functions */
 int /*<<< orphan*/  integer ; 
 int /*<<< orphan*/  map_close ; 
 int /*<<< orphan*/  map_open ; 
 int /*<<< orphan*/  y (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ystr (char const*) ; 

__attribute__((used)) static void dump_rect(yajl_gen gen, const char *name, Rect r) {
    ystr(name);
    y(map_open);
    ystr("x");
    y(integer, r.x);
    ystr("y");
    y(integer, r.y);
    ystr("width");
    y(integer, r.width);
    ystr("height");
    y(integer, r.height);
    y(map_close);
}