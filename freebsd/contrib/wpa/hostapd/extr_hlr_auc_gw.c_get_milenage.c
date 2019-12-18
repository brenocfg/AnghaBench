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
struct milenage_parameters {struct milenage_parameters* next; int /*<<< orphan*/  imsi; } ;

/* Variables and functions */
 struct milenage_parameters* db_get_milenage (char const*) ; 
 struct milenage_parameters* milenage_db ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct milenage_parameters * get_milenage(const char *imsi)
{
	struct milenage_parameters *m = milenage_db;

	while (m) {
		if (strcmp(m->imsi, imsi) == 0)
			break;
		m = m->next;
	}

#ifdef CONFIG_SQLITE
	if (!m)
		m = db_get_milenage(imsi);
#endif /* CONFIG_SQLITE */

	return m;
}