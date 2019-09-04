#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  index_type ;
typedef  int /*<<< orphan*/  char_type ;
struct TYPE_5__ {int /*<<< orphan*/  xnum; } ;
typedef  TYPE_1__ LineBuf ;

/* Variables and functions */
 int /*<<< orphan*/  clear_chars_in_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_lineptr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_lineptr (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
clear_chars_to(LineBuf* linebuf, index_type y, char_type ch) {
    clear_chars_in_line(cpu_lineptr(linebuf, y), gpu_lineptr(linebuf, y), linebuf->xnum, ch);
}