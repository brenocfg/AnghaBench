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
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* svn_checksum_serialize (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bind_text (int /*<<< orphan*/ *,int,char const*) ; 

svn_error_t *
svn_sqlite__bind_checksum(svn_sqlite__stmt_t *stmt,
                          int slot,
                          const svn_checksum_t *checksum,
                          apr_pool_t *scratch_pool)
{
  const char *csum_str;

  if (checksum == NULL)
    csum_str = NULL;
  else
    csum_str = svn_checksum_serialize(checksum, scratch_pool, scratch_pool);

  return svn_error_trace(svn_sqlite__bind_text(stmt, slot, csum_str));
}