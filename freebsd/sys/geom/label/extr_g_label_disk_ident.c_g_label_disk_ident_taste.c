#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_consumer {TYPE_2__* provider; } ;
struct g_class {char* name; } ;
typedef  int /*<<< orphan*/  ident ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_class* class; } ;

/* Variables and functions */
 int DISK_IDENT_SIZE ; 
 int /*<<< orphan*/ ** classes_pass ; 
 scalar_t__ g_io_getattr (char*,struct g_consumer*,int*,char*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
g_label_disk_ident_taste(struct g_consumer *cp, char *label, size_t size)
{
	struct g_class *cls;
	char ident[DISK_IDENT_SIZE];
	int ident_len, found, i;

	g_topology_assert_not();
	label[0] = '\0';

	cls = cp->provider->geom->class;

	/* 
	 * Get the GEOM::ident string, and construct a label in the format
	 * "CLASS_NAME-ident"
	 */
	ident_len = sizeof(ident);
	if (g_io_getattr("GEOM::ident", cp, &ident_len, ident) == 0) {
		if (ident_len == 0 || ident[0] == '\0')
			return;
		for (i = 0, found = 0; classes_pass[i] != NULL; i++)
			if (strcmp(classes_pass[i], cls->name) == 0) {
				found = 1;
				break;
			}
		if (!found)
			return;
		/*
		 * We can safely ignore the result of snprintf(): the label
		 * will simply be truncated, which at most is only annoying.
		 */
		(void)snprintf(label, size, "%s-%s", cls->name, ident);
	}
}