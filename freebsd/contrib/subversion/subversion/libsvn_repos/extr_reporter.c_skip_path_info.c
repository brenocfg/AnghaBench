#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  reader; TYPE_3__* lookahead; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ report_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_path_info (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ relevant (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
skip_path_info(report_baton_t *b, const char *prefix)
{
  apr_size_t plen = strlen(prefix);
  apr_pool_t *subpool;

  while (relevant(b->lookahead, prefix, plen))
    {
      svn_pool_destroy(b->lookahead->pool);
      subpool = svn_pool_create(b->pool);
      SVN_ERR(read_path_info(&b->lookahead, b->reader, subpool));
    }
  return SVN_NO_ERROR;
}