#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {int /*<<< orphan*/  mctx; int /*<<< orphan*/  sources; } ;
typedef  TYPE_1__ isc_lex_t ;
struct TYPE_9__ {int /*<<< orphan*/  pushback; int /*<<< orphan*/  name; scalar_t__ input; scalar_t__ need_close; scalar_t__ is_file; } ;
typedef  TYPE_2__ inputsource ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_2__* HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_LEX (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  link ; 

isc_result_t
isc_lex_close(isc_lex_t *lex) {
	inputsource *source;

	/*
	 * Close the most recently opened object (i.e. file or buffer).
	 */

	REQUIRE(VALID_LEX(lex));

	source = HEAD(lex->sources);
	if (source == NULL)
		return (ISC_R_NOMORE);

	ISC_LIST_UNLINK(lex->sources, source, link);
	if (source->is_file) {
		if (source->need_close)
			(void)fclose((FILE *)(source->input));
	}
	isc_mem_free(lex->mctx, source->name);
	isc_buffer_free(&source->pushback);
	isc_mem_put(lex->mctx, source, sizeof(*source));

	return (ISC_R_SUCCESS);
}