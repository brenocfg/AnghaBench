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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  RA_SERF_DESCRIPTION_VER ; 
 int /*<<< orphan*/  SERF_MAJOR_VERSION ; 
 int /*<<< orphan*/  SERF_MINOR_VERSION ; 
 int /*<<< orphan*/  SERF_PATCH_VERSION ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_lib_version (int*,int*,int*) ; 

__attribute__((used)) static const char *
ra_serf_get_description(apr_pool_t *pool)
{
  int major, minor, patch;

  serf_lib_version(&major, &minor, &patch);
  return apr_psprintf(pool, _(RA_SERF_DESCRIPTION_VER),
                      major, minor, patch,
                      SERF_MAJOR_VERSION,
                      SERF_MINOR_VERSION,
                      SERF_PATCH_VERSION
                      );
}