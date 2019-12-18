#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_lexspecials_t ;
struct TYPE_4__ {int /*<<< orphan*/  specials; } ;
typedef  TYPE_1__ isc_lex_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_LEX (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
isc_lex_setspecials(isc_lex_t *lex, isc_lexspecials_t specials) {
	/*
	 * The characters in 'specials' are returned as tokens.  Along with
	 * whitespace, they delimit strings and numbers.
	 */

	REQUIRE(VALID_LEX(lex));

	memcpy(lex->specials, specials, 256);
}