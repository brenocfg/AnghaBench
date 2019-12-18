#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ current_line; int /*<<< orphan*/  write_baton; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  eol_str; int /*<<< orphan*/  eof; } ;
typedef  TYPE_1__ target_content_t ;
typedef  scalar_t__ svn_linenum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readline (TYPE_1__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_lines_to_target(target_content_t *content, svn_linenum_t line,
                     apr_pool_t *pool)
{
  apr_pool_t *iterpool;

  iterpool = svn_pool_create(pool);
  while ((content->current_line < line || line == 0) && ! content->eof)
    {
      const char *target_line;
      apr_size_t len;

      svn_pool_clear(iterpool);

      SVN_ERR(readline(content, &target_line, iterpool, iterpool));
      if (! content->eof)
        target_line = apr_pstrcat(iterpool, target_line, content->eol_str,
                                  SVN_VA_NULL);
      len = strlen(target_line);
      SVN_ERR(content->write(content->write_baton, target_line,
                             len, iterpool));
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}