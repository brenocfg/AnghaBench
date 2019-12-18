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
 char const* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
subtract_anchor(const char *anchor, const char *url, apr_pool_t *pool)
{
  return svn_uri_skip_ancestor(anchor, url, pool);
}