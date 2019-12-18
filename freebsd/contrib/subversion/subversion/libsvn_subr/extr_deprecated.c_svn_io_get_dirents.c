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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_io_get_dirents2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_get_dirents(apr_hash_t **dirents,
                   const char *path,
                   apr_pool_t *pool)
{
  /* Note that in C, padding is not allowed at the beginning of structs,
     so this is actually portable, since the kind field of svn_io_dirent_t
     is first in that struct. */
  return svn_io_get_dirents2(dirents, path, pool);
}