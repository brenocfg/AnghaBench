#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_7__ {int /*<<< orphan*/  sources; int /*<<< orphan*/  mctx; int /*<<< orphan*/  max_token; } ;
typedef  TYPE_1__ isc_lex_t ;
typedef  void* isc_boolean_t ;
struct TYPE_8__ {int line; scalar_t__ ignored; int /*<<< orphan*/ * name; int /*<<< orphan*/ * pushback; void* input; int /*<<< orphan*/  at_eof; void* need_close; void* is_file; scalar_t__ result; } ;
typedef  TYPE_2__ inputsource ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_LIST_INITANDPREPEND (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ isc_buffer_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_mem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * isc_mem_strdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static inline isc_result_t
new_source(isc_lex_t *lex, isc_boolean_t is_file, isc_boolean_t need_close,
	   void *input, const char *name)
{
	inputsource *source;
	isc_result_t result;

	source = isc_mem_get(lex->mctx, sizeof(*source));
	if (source == NULL)
		return (ISC_R_NOMEMORY);
	source->result = ISC_R_SUCCESS;
	source->is_file = is_file;
	source->need_close = need_close;
	source->at_eof = ISC_FALSE;
	source->input = input;
	source->name = isc_mem_strdup(lex->mctx, name);
	if (source->name == NULL) {
		isc_mem_put(lex->mctx, source, sizeof(*source));
		return (ISC_R_NOMEMORY);
	}
	source->pushback = NULL;
	result = isc_buffer_allocate(lex->mctx, &source->pushback,
				     lex->max_token);
	if (result != ISC_R_SUCCESS) {
		isc_mem_free(lex->mctx, source->name);
		isc_mem_put(lex->mctx, source, sizeof(*source));
		return (result);
	}
	source->ignored = 0;
	source->line = 1;
	ISC_LIST_INITANDPREPEND(lex->sources, source, link);

	return (ISC_R_SUCCESS);
}