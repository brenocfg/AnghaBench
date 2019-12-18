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
typedef  int apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_spillbuf__reader_getc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_number(apr_uint64_t *num, svn_spillbuf_reader_t *reader, apr_pool_t *pool)
{
  char c;

  *num = 0;
  while (1)
    {
      SVN_ERR(svn_spillbuf__reader_getc(&c, reader, pool));
      if (c == ':')
        break;
      *num = *num * 10 + (c - '0');
    }
  return SVN_NO_ERROR;
}