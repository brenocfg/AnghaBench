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
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ SPA_VERSION_RECVD_PROPS ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPROP_HAS_RECVD ; 
 int dsl_prop_set_int (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_prop_set_hasrecvd_impl(const char *dsname, zprop_source_t source)
{
	uint64_t version;
	spa_t *spa;
	int error = 0;

	VERIFY0(spa_open(dsname, &spa, FTAG));
	version = spa_version(spa);
	spa_close(spa, FTAG);

	if (version >= SPA_VERSION_RECVD_PROPS)
		error = dsl_prop_set_int(dsname, ZPROP_HAS_RECVD, source, 0);
	return (error);
}