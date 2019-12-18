#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; } ;
typedef  TYPE_1__ isc_token_t ;
struct TYPE_12__ {unsigned char* base; scalar_t__ length; } ;
typedef  TYPE_2__ isc_region_t ;
struct TYPE_13__ {int /*<<< orphan*/  sources; } ;
typedef  TYPE_3__ isc_lex_t ;
struct TYPE_14__ {scalar_t__ ignored; int /*<<< orphan*/  pushback; } ;
typedef  TYPE_4__ inputsource ;

/* Variables and functions */
 TYPE_4__* HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNUSED (TYPE_1__*) ; 
 int VALID_LEX (TYPE_3__*) ; 
 scalar_t__ isc_buffer_base (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_buffer_consumedlength (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_tokentype_eof ; 

void
isc_lex_getlasttokentext(isc_lex_t *lex, isc_token_t *tokenp, isc_region_t *r)
{
	inputsource *source;

	REQUIRE(VALID_LEX(lex));
	source = HEAD(lex->sources);
	REQUIRE(source != NULL);
	REQUIRE(tokenp != NULL);
	REQUIRE(isc_buffer_consumedlength(source->pushback) != 0 ||
		tokenp->type == isc_tokentype_eof);

	UNUSED(tokenp);

	INSIST(source->ignored <= isc_buffer_consumedlength(source->pushback));
	r->base = (unsigned char *)isc_buffer_base(source->pushback) +
		  source->ignored;
	r->length = isc_buffer_consumedlength(source->pushback) -
		    source->ignored;
}