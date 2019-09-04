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
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 scalar_t__ EQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bg ; 
 int /*<<< orphan*/  blink ; 
 int /*<<< orphan*/  bold ; 
 int /*<<< orphan*/  decoration ; 
 int /*<<< orphan*/  decoration_fg ; 
 int /*<<< orphan*/  dim ; 
 int /*<<< orphan*/  fg ; 
 int /*<<< orphan*/  italic ; 
 int /*<<< orphan*/  reverse ; 
 int /*<<< orphan*/  shape ; 
 int /*<<< orphan*/  strikethrough ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

__attribute__((used)) static int __eq__(Cursor *a, Cursor *b) {
    return EQ(bold) && EQ(italic) && EQ(strikethrough) && EQ(dim) && EQ(reverse) && EQ(decoration) && EQ(fg) && EQ(bg) && EQ(decoration_fg) && EQ(x) && EQ(y) && EQ(shape) && EQ(blink);
}