#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fulltext_cache; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_SIZE_MAX ; 
 scalar_t__ svn_cache__is_cachable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_boolean_t
fulltext_size_is_cachable(svn_fs_x__data_t *ffd,
                          svn_filesize_t size)
{
  return (size < APR_SIZE_MAX)
      && svn_cache__is_cachable(ffd->fulltext_cache, (apr_size_t)size);
}