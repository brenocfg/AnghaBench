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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_portset_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/ * isc_mem_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

isc_result_t
isc_portset_create(isc_mem_t *mctx, isc_portset_t **portsetp) {
	isc_portset_t *portset;

	REQUIRE(portsetp != NULL && *portsetp == NULL);

	portset = isc_mem_get(mctx, sizeof(*portset));
	if (portset == NULL)
		return (ISC_R_NOMEMORY);

	/* Make the set 'empty' by default */
	memset(portset, 0, sizeof(*portset));
	*portsetp = portset;

	return (ISC_R_SUCCESS);
}