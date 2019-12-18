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
struct recode_write_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_cmdline_fputs (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *recode_write(void *baton,
                                 const char *data,
                                 apr_size_t *len)
{
  struct recode_write_baton *rwb = baton;
  svn_pool_clear(rwb->pool);
  return svn_cmdline_fputs(data, rwb->out, rwb->pool);
}