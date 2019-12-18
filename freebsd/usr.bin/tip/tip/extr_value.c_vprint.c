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
struct TYPE_3__ {char* v_name; int v_type; int /*<<< orphan*/  v_value; } ;
typedef  TYPE_1__ value_t ;

/* Variables and functions */
#define  BOOL 131 
#define  CHAR 130 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MIDDLE ; 
#define  NUMBER 129 
#define  STRING 128 
 int TMASK ; 
 int /*<<< orphan*/  boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  character (int /*<<< orphan*/ ) ; 
 scalar_t__ col ; 
 char* ctrl (int /*<<< orphan*/ ) ; 
 char* interp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ size (char*) ; 

__attribute__((used)) static void
vprint(value_t *p)
{
	char *cp;

	if (col > 0 && col < MIDDLE)
		while (col++ < MIDDLE)
			putchar(' ');
	col += size(p->v_name);
	switch (p->v_type&TMASK) {

	case BOOL:
		if (boolean(p->v_value) == FALSE) {
			col++;
			putchar('!');
		}
		printf("%s", p->v_name);
		break;

	case STRING:
		printf("%s=", p->v_name);
		col++;
		if (p->v_value) {
			cp = interp(p->v_value);
			col += size(cp);
			printf("%s", cp);
		}
		break;

	case NUMBER:
		col += 6;
		printf("%s=%-5ld", p->v_name, number(p->v_value));
		break;

	case CHAR:
		printf("%s=", p->v_name);
		col++;
		if (p->v_value) {
			cp = ctrl(character(p->v_value));
			col += size(cp);
			printf("%s", cp);
		}
		break;
	}
	if (col >= MIDDLE) {
		col = 0;
		printf("\r\n");
		return;
	}
}