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
 int /*<<< orphan*/  RA_LOCAL_DESCRIPTION ; 
 char const* _ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
svn_ra_local__get_description(apr_pool_t *pool)
{
  return _(RA_LOCAL_DESCRIPTION);
}