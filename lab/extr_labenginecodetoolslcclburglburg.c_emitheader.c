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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print (char*,...) ; 
 int /*<<< orphan*/  rcsid ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emitheader(void) {
	time_t timer = time(NULL);

	print("/*\ngenerated at %sby %s\n*/\n", ctime(&timer), rcsid);
	print("static void %Pkids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);\n");
	print("static void %Plabel(NODEPTR_TYPE);\n");
	print("static int %Prule(void*, int);\n\n");
}