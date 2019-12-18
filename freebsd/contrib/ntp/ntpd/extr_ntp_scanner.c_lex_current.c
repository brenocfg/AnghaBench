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
struct FILE_INFO {int dummy; } ;

/* Variables and functions */
 struct FILE_INFO* lex_stack ; 

struct FILE_INFO *
lex_current()
{
	/* this became so simple, it could be a macro. But then,
	 * lex_stack needed to be global...
	 */
	return lex_stack;
}