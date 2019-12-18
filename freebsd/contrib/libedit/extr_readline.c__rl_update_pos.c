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
struct TYPE_3__ {scalar_t__ buffer; scalar_t__ lastchar; scalar_t__ cursor; } ;
typedef  TYPE_1__ LineInfo ;

/* Variables and functions */
 int /*<<< orphan*/  e ; 
 TYPE_1__* el_line (int /*<<< orphan*/ ) ; 
 size_t rl_end ; 
 char* rl_line_buffer ; 
 int rl_point ; 

__attribute__((used)) static void
_rl_update_pos(void)
{
	const LineInfo *li = el_line(e);

	rl_point = (int)(li->cursor - li->buffer);
	rl_end = (int)(li->lastchar - li->buffer);
	rl_line_buffer[rl_end] = '\0';
}