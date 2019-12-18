#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ref_list {int nr; TYPE_1__* list; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int list_refs(struct ref_list *r, int argc, const char **argv)
{
	int i;

	for (i = 0; i < r->nr; i++) {
		if (argc > 1) {
			int j;
			for (j = 1; j < argc; j++)
				if (!strcmp(r->list[i].name, argv[j]))
					break;
			if (j == argc)
				continue;
		}
		printf("%s %s\n", oid_to_hex(&r->list[i].oid),
				r->list[i].name);
	}
	return 0;
}