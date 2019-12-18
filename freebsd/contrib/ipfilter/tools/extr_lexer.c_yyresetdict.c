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
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ yydebug ; 
 scalar_t__ yydictfixed ; 
 int yysavedepth ; 
 int /*<<< orphan*/ * yysavewords ; 
 int /*<<< orphan*/  yysettab (int /*<<< orphan*/ ) ; 

void yyresetdict()
{
	if (yydebug)
		printf("yyresetdict(%d)\n", yysavedepth);
	if (yysavedepth > 0) {
		yysettab(yysavewords[--yysavedepth]);
		if (yydebug)
			printf("yysavedepth-- => %d\n", yysavedepth);
	}
	yydictfixed = 0;
}