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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 

const char *
svn_log__get_location_segments(const char *path, svn_revnum_t peg_revision,
                               svn_revnum_t start, svn_revnum_t end,
                               apr_pool_t *pool)
{
  return apr_psprintf(pool, "get-location-segments %s@%ld r%ld:%ld",
                      svn_path_uri_encode(path, pool),
                      peg_revision, start, end);
}