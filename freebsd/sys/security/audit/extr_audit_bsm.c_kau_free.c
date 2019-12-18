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
struct au_token {struct au_token* data; scalar_t__ len; scalar_t__ used; struct au_token* t_data; int /*<<< orphan*/  token_q; } ;
struct au_record {struct au_record* data; scalar_t__ len; scalar_t__ used; struct au_record* t_data; int /*<<< orphan*/  token_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AUDITBSM ; 
 struct au_token* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct au_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct au_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tokens ; 

void
kau_free(struct au_record *rec)
{
	struct au_token *tok;

	/* Free the token list. */
	while ((tok = TAILQ_FIRST(&rec->token_q))) {
		TAILQ_REMOVE(&rec->token_q, tok, tokens);
		free(tok->t_data, M_AUDITBSM);
		free(tok, M_AUDITBSM);
	}

	rec->used = 0;
	rec->len = 0;
	free(rec->data, M_AUDITBSM);
	free(rec, M_AUDITBSM);
}