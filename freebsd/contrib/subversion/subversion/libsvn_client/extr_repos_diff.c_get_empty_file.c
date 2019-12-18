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
struct edit_baton {char* empty_file; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_io_file_del_on_pool_cleanup ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_empty_file(struct edit_baton *eb,
               const char **empty_file_path)
{
  /* Create the file if it does not exist */
  /* Note that we tried to use /dev/null in r857294, but
     that won't work on Windows: it's impossible to stat NUL */
  if (!eb->empty_file)
    SVN_ERR(svn_io_open_unique_file3(NULL, &(eb->empty_file), NULL,
                                     svn_io_file_del_on_pool_cleanup,
                                     eb->pool, eb->pool));

  *empty_file_path = eb->empty_file;

  return SVN_NO_ERROR;
}