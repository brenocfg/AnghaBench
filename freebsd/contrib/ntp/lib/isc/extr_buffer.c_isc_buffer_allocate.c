#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mctx; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_buffer_init (TYPE_1__*,unsigned char*,unsigned int) ; 
 TYPE_1__* isc_mem_get (int /*<<< orphan*/ *,unsigned int) ; 

isc_result_t
isc_buffer_allocate(isc_mem_t *mctx, isc_buffer_t **dynbuffer,
		    unsigned int length)
{
	isc_buffer_t *dbuf;

	REQUIRE(dynbuffer != NULL);
	REQUIRE(*dynbuffer == NULL);

	dbuf = isc_mem_get(mctx, length + sizeof(isc_buffer_t));
	if (dbuf == NULL)
		return (ISC_R_NOMEMORY);

	isc_buffer_init(dbuf, ((unsigned char *)dbuf) + sizeof(isc_buffer_t),
			length);
	dbuf->mctx = mctx;

	*dynbuffer = dbuf;

	return (ISC_R_SUCCESS);
}