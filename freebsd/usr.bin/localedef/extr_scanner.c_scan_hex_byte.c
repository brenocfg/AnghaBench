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
 int hex (int) ; 
 int /*<<< orphan*/  isxdigit (int) ; 
 int scanc () ; 
 int /*<<< orphan*/  yyerror (char*) ; 

__attribute__((used)) static int
scan_hex_byte(void)
{
	int	c1, c2;
	int	v;

	c1 = scanc();
	if (!isxdigit(c1)) {
		yyerror("malformed hex digit");
		return (0);
	}
	c2 = scanc();
	if (!isxdigit(c2)) {
		yyerror("malformed hex digit");
		return (0);
	}
	v = ((hex(c1) << 4) | hex(c2));
	return (v);
}