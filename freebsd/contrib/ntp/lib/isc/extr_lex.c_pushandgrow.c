#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_uint8_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_region_t ;
struct TYPE_13__ {int /*<<< orphan*/  mctx; } ;
typedef  TYPE_1__ isc_lex_t ;
struct TYPE_14__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_2__ isc_buffer_t ;
struct TYPE_15__ {TYPE_2__* pushback; } ;
typedef  TYPE_3__ inputsource ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ isc_buffer_allocate (int /*<<< orphan*/ ,TYPE_2__**,unsigned int) ; 
 scalar_t__ isc_buffer_availablelength (TYPE_2__*) ; 
 scalar_t__ isc_buffer_copyregion (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_free (TYPE_2__**) ; 
 unsigned int isc_buffer_length (TYPE_2__*) ; 
 int /*<<< orphan*/  isc_buffer_putuint8 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_buffer_usedregion (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_result_t
pushandgrow(isc_lex_t *lex, inputsource *source, int c) {
	if (isc_buffer_availablelength(source->pushback) == 0) {
		isc_buffer_t *tbuf = NULL;
		unsigned int oldlen;
		isc_region_t used;
		isc_result_t result;

		oldlen = isc_buffer_length(source->pushback);
		result = isc_buffer_allocate(lex->mctx, &tbuf, oldlen * 2);
		if (result != ISC_R_SUCCESS)
			return (result);
		isc_buffer_usedregion(source->pushback, &used);
		result = isc_buffer_copyregion(tbuf, &used);
		INSIST(result == ISC_R_SUCCESS);
		tbuf->current = source->pushback->current;
		isc_buffer_free(&source->pushback);
		source->pushback = tbuf;
	}
	isc_buffer_putuint8(source->pushback, (isc_uint8_t)c);
	return (ISC_R_SUCCESS);
}