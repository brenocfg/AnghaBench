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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_lex_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_LEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ *) ; 

isc_result_t
isc_lex_openbuffer(isc_lex_t *lex, isc_buffer_t *buffer) {
	char name[128];

	/*
	 * Make 'buffer' the current input source for 'lex'.
	 */

	REQUIRE(VALID_LEX(lex));

	snprintf(name, sizeof(name), "buffer-%p", buffer);

	return (new_source(lex, ISC_FALSE, ISC_FALSE, buffer, name));
}