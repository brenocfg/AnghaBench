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
struct gsm_triplet {struct gsm_triplet* next; int /*<<< orphan*/  imsi; } ;

/* Variables and functions */
 struct gsm_triplet* gsm_db ; 
 struct gsm_triplet* gsm_db_pos ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct gsm_triplet * get_gsm_triplet(const char *imsi)
{
	struct gsm_triplet *g = gsm_db_pos;

	while (g) {
		if (strcmp(g->imsi, imsi) == 0) {
			gsm_db_pos = g->next;
			return g;
		}
		g = g->next;
	}

	g = gsm_db;
	while (g && g != gsm_db_pos) {
		if (strcmp(g->imsi, imsi) == 0) {
			gsm_db_pos = g->next;
			return g;
		}
		g = g->next;
	}

	return NULL;
}