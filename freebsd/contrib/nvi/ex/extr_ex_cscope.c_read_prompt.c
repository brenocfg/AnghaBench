#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  from_fp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ CSC ;

/* Variables and functions */
 int* CSCOPE_PROMPT ; 
 int EOF ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminate (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_prompt(SCR *sp, CSC *csc)
{
	int ch;

#define	CSCOPE_PROMPT		">> "
	for (;;) {
		while ((ch =
		    getc(csc->from_fp)) != EOF && ch != CSCOPE_PROMPT[0]);
		if (ch == EOF) {
			terminate(sp, csc, 0);
			return (1);
		}
		if (getc(csc->from_fp) != CSCOPE_PROMPT[1])
			continue;
		if (getc(csc->from_fp) != CSCOPE_PROMPT[2])
			continue;
		break;
	}
	return (0);
}