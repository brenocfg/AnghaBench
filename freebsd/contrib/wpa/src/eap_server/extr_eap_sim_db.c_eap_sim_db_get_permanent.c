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
struct eap_sim_pseudonym {char const* permanent; struct eap_sim_pseudonym* next; int /*<<< orphan*/  pseudonym; } ;
struct eap_sim_db_data {struct eap_sim_pseudonym* pseudonyms; scalar_t__ sqlite_db; } ;

/* Variables and functions */
 char const* db_get_pseudonym (struct eap_sim_db_data*,char const*) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char const*) ; 

const char *
eap_sim_db_get_permanent(struct eap_sim_db_data *data, const char *pseudonym)
{
	struct eap_sim_pseudonym *p;

#ifdef CONFIG_SQLITE
	if (data->sqlite_db)
		return db_get_pseudonym(data, pseudonym);
#endif /* CONFIG_SQLITE */

	p = data->pseudonyms;
	while (p) {
		if (os_strcmp(p->pseudonym, pseudonym) == 0)
			return p->permanent;
		p = p->next;
	}

	return NULL;
}