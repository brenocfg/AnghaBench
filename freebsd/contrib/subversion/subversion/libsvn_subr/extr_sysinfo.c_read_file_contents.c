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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stringbuf_from_file2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_stringbuf_t *
read_file_contents(const char *filename, apr_pool_t *pool)
{
  svn_error_t *err;
  svn_stringbuf_t *buffer;

  err = svn_stringbuf_from_file2(&buffer, filename, pool);
  if (err)
    {
      svn_error_clear(err);
      return NULL;
    }

  return buffer;
}