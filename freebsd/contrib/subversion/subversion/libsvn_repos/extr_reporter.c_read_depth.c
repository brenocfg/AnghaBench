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
typedef  int /*<<< orphan*/  svn_spillbuf_reader_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_REPOS_BAD_REVISION_REPORT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_depth_exclude ; 
 int /*<<< orphan*/  svn_depth_files ; 
 int /*<<< orphan*/  svn_depth_immediates ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char,char const*) ; 
 int /*<<< orphan*/  svn_spillbuf__reader_getc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_depth(svn_depth_t *depth, svn_spillbuf_reader_t *reader, const char *path,
           apr_pool_t *pool)
{
  char c;

  SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
  switch (c)
    {
    case 'X':
      *depth = svn_depth_exclude;
      break;
    case 'E':
      *depth = svn_depth_empty;
      break;
    case 'F':
      *depth = svn_depth_files;
      break;
    case 'M':
      *depth = svn_depth_immediates;
      break;

      /* Note that we do not tolerate explicit representation of
         svn_depth_infinity here, because that's not how
         write_path_info() writes it. */
    default:
      return svn_error_createf(SVN_ERR_REPOS_BAD_REVISION_REPORT, NULL,
                               _("Invalid depth (%c) for path '%s'"), c, path);
    }

  return SVN_NO_ERROR;
}