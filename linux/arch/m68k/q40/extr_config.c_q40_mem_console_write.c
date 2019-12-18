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
struct console {int dummy; } ;

/* Variables and functions */
 unsigned int _cpleft ; 
 int /*<<< orphan*/ * q40_mem_cptr ; 

__attribute__((used)) static void q40_mem_console_write(struct console *co, const char *s,
				  unsigned int count)
{
	const char *p = s;

	if (count < _cpleft) {
		while (count-- > 0) {
			*q40_mem_cptr = *p++;
			q40_mem_cptr += 4;
			_cpleft--;
		}
	}
}