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
struct eap_sim_reauth {struct eap_sim_reauth* next; } ;
struct eap_sim_pseudonym {struct eap_sim_pseudonym* next; } ;
struct eap_sim_db_pending {struct eap_sim_db_pending* next; } ;
struct eap_sim_db_data {struct eap_sim_db_pending* pending; struct eap_sim_reauth* reauths; struct eap_sim_pseudonym* pseudonyms; struct eap_sim_db_data* fname; int /*<<< orphan*/ * sqlite_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_sim_db_close_socket (struct eap_sim_db_data*) ; 
 int /*<<< orphan*/  eap_sim_db_free_pending (struct eap_sim_db_data*,struct eap_sim_db_pending*) ; 
 int /*<<< orphan*/  eap_sim_db_free_pseudonym (struct eap_sim_pseudonym*) ; 
 int /*<<< orphan*/  eap_sim_db_free_reauth (struct eap_sim_reauth*) ; 
 int /*<<< orphan*/  os_free (struct eap_sim_db_data*) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 

void eap_sim_db_deinit(void *priv)
{
	struct eap_sim_db_data *data = priv;
	struct eap_sim_pseudonym *p, *prev;
	struct eap_sim_reauth *r, *prevr;
	struct eap_sim_db_pending *pending, *prev_pending;

#ifdef CONFIG_SQLITE
	if (data->sqlite_db) {
		sqlite3_close(data->sqlite_db);
		data->sqlite_db = NULL;
	}
#endif /* CONFIG_SQLITE */

	eap_sim_db_close_socket(data);
	os_free(data->fname);

	p = data->pseudonyms;
	while (p) {
		prev = p;
		p = p->next;
		eap_sim_db_free_pseudonym(prev);
	}

	r = data->reauths;
	while (r) {
		prevr = r;
		r = r->next;
		eap_sim_db_free_reauth(prevr);
	}

	pending = data->pending;
	while (pending) {
		prev_pending = pending;
		pending = pending->next;
		eap_sim_db_free_pending(data, prev_pending);
	}

	os_free(data);
}