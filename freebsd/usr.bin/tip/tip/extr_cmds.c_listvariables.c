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
struct TYPE_3__ {int v_type; int /*<<< orphan*/  v_value; scalar_t__ v_name; } ;
typedef  TYPE_1__ value_t ;

/* Variables and functions */
#define  BOOL 131 
#define  CHAR 130 
#define  NUMBER 129 
#define  STRING 128 
 int TMASK ; 
 int /*<<< orphan*/  VIS_WHITE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  character (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strvis (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vis (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vtable ; 

void
listvariables(int c)
{
	value_t *p;
	char *buf;
	char charbuf[5];	/* for vis(3), 4 chars for encoding, plus nul */

	puts("v\r");
	for (p = vtable; p->v_name; p++) {
		fputs(p->v_name, stdout);
		switch (p->v_type&TMASK) {
		case STRING:
			if (p->v_value) {
				buf = malloc(4*strlen(p->v_value) + 1);
				if (buf == NULL) {
					fprintf(stderr, "Unable to malloc()\n");
					abort();
				}
				strvis(buf, p->v_value, VIS_WHITE);
				printf(" %s", buf);
				free(buf);
			}
			putchar('\r');
			putchar('\n');
			break;
		case NUMBER:
			printf(" %ld\r\n", number(p->v_value));
			break;
		case BOOL:
			printf(" %s\r\n",
			    !boolean(p->v_value) ? "false" : "true");
			break;
		case CHAR:
			vis(charbuf, character(p->v_value), VIS_WHITE, 0);
			printf(" %s\r\n", charbuf);
			break;
		}
	}
}