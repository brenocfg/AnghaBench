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

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  shelf_name_decode (char**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static svn_error_t *
shelf_name_from_filename(char **name,
                         const char *filename,
                         apr_pool_t *result_pool)
{
  size_t len = strlen(filename);

  if (len > 6 && strcmp(filename + len - 6, ".patch") == 0)
    {
      char *codename = apr_pstrndup(result_pool, filename, len - 6);
      SVN_ERR(shelf_name_decode(name, codename, result_pool));
    }
  return SVN_NO_ERROR;
}