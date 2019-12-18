#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_token; int /*<<< orphan*/  mctx; scalar_t__ magic; struct TYPE_6__* data; int /*<<< orphan*/  sources; } ;
typedef  TYPE_1__ isc_lex_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  VALID_LEX (TYPE_1__*) ; 
 scalar_t__ isc_lex_close (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
isc_lex_destroy(isc_lex_t **lexp) {
	isc_lex_t *lex;

	/*
	 * Destroy the lexer.
	 */

	REQUIRE(lexp != NULL);
	lex = *lexp;
	REQUIRE(VALID_LEX(lex));

	while (!EMPTY(lex->sources))
		RUNTIME_CHECK(isc_lex_close(lex) == ISC_R_SUCCESS);
	if (lex->data != NULL)
		isc_mem_put(lex->mctx, lex->data, lex->max_token + 1);
	lex->magic = 0;
	isc_mem_put(lex->mctx, lex, sizeof(*lex));

	*lexp = NULL;
}