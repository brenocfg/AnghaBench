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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INT64_BUFFER_SIZE ; 
 char* apr_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 

const char *
svn_fs_x__txn_name(svn_fs_x__txn_id_t txn_id,
                   apr_pool_t *result_pool)
{
  char *p = apr_palloc(result_pool, SVN_INT64_BUFFER_SIZE);
  svn__ui64tobase36(p, txn_id);
  return p;
}