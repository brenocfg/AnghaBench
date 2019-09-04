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
struct ref {char* symref; char* name; int /*<<< orphan*/  old_oid; struct ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void output_refs(struct ref *refs)
{
	struct ref *posn;
	for (posn = refs; posn; posn = posn->next) {
		if (posn->symref)
			printf("@%s %s\n", posn->symref, posn->name);
		else
			printf("%s %s\n", oid_to_hex(&posn->old_oid), posn->name);
	}
	printf("\n");
	fflush(stdout);
}