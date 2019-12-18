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

/* Variables and functions */
 int qfalse ; 
 int qtrue ; 

int IsWhiteSpace(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '(' || c == ')'
		|| c == '?' || c == ':'
		|| c == '\''|| c == '/'
		|| c == ',' || c == '.'
		|| c == '['	|| c == ']'
		|| c == '-' || c == '_'
		|| c == '+' || c == '=') return qfalse;
	return qtrue;
}