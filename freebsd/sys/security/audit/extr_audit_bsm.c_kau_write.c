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
struct au_token {scalar_t__ len; } ;
struct au_record {int /*<<< orphan*/  len; int /*<<< orphan*/  token_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct au_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static void
kau_write(struct au_record *rec, struct au_token *tok)
{

	KASSERT(tok != NULL, ("kau_write: tok == NULL"));

	TAILQ_INSERT_TAIL(&rec->token_q, tok, tokens);
	rec->len += tok->len;
}