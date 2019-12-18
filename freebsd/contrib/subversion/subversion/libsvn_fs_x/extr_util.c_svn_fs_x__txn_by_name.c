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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn__base36toui64 (char const**,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 

svn_error_t *
svn_fs_x__txn_by_name(svn_fs_x__txn_id_t *txn_id,
                      const char *txn_name)
{
  const char *next;
  apr_uint64_t id = svn__base36toui64(&next, txn_name);
  if (next == NULL || *next != 0 || *txn_name == 0)
    return svn_error_createf(SVN_ERR_INCORRECT_PARAMS, NULL,
                             "Malformed TXN name '%s'", txn_name);

  *txn_id = id;
  return SVN_NO_ERROR;
}