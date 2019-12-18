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
struct TYPE_3__ {char* template; int /*<<< orphan*/  ern; struct TYPE_3__* link; } ;
typedef  TYPE_1__* Rule ;

/* Variables and functions */
 int /*<<< orphan*/  print (char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void emitstring(Rule rules) {
	Rule r;

	print("static char *%Ptemplates[] = {\n");
	print("/* 0 */%10,\n");
	for (r = rules; r; r = r->link)
		print("/* %d */%1\"%s\",%1/* %R */\n", r->ern, r->template, r);
	print("};\n");
	print("\nstatic char %Pisinstruction[] = {\n");
	print("/* 0 */%10,\n");
	for (r = rules; r; r = r->link) {
		int len = strlen(r->template);
		print("/* %d */%1%d,%1/* %s */\n", r->ern,
			len >= 2 && r->template[len-2] == '\\' && r->template[len-1] == 'n',
			r->template);
	}
	print("};\n");
	print("\nstatic char *%Pstring[] = {\n");
	print("/* 0 */%10,\n");
	for (r = rules; r; r = r->link)
		print("/* %d */%1\"%R\",\n", r->ern, r);
	print("};\n\n");
}