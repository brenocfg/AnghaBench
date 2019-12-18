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
typedef  int /*<<< orphan*/  svn_spillbuf_reader_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int start_empty; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * lock_token; int /*<<< orphan*/  depth; int /*<<< orphan*/ * path; int /*<<< orphan*/  rev; int /*<<< orphan*/ * link_path; } ;
typedef  TYPE_1__ path_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_string (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_spillbuf__reader_getc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_path_info(path_info_t **pi,
               svn_spillbuf_reader_t *reader,
               apr_pool_t *pool)
{
  char c;

  SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
  if (c == '-')
    {
      *pi = NULL;
      return SVN_NO_ERROR;
    }

  *pi = apr_palloc(pool, sizeof(**pi));
  SVN_ERR(read_string(&(*pi)->path, reader, pool));
  SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
  if (c == '+')
    SVN_ERR(read_string(&(*pi)->link_path, reader, pool));
  else
    (*pi)->link_path = NULL;
  SVN_ERR(read_rev(&(*pi)->rev, reader, pool));
  SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
  if (c == '+')
    SVN_ERR(read_depth(&((*pi)->depth), reader, (*pi)->path, pool));
  else
    (*pi)->depth = svn_depth_infinity;
  SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
  (*pi)->start_empty = (c == '+');
  SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
  if (c == '+')
    SVN_ERR(read_string(&(*pi)->lock_token, reader, pool));
  else
    (*pi)->lock_token = NULL;
  (*pi)->pool = pool;
  return SVN_NO_ERROR;
}