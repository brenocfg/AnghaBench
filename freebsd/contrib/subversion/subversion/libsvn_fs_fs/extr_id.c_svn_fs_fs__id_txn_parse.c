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
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_MALFORMED_TXN_ID ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  txn_id_parse (int /*<<< orphan*/ *,char const*) ; 

svn_error_t *
svn_fs_fs__id_txn_parse(svn_fs_fs__id_part_t *txn_id,
                        const char *data)
{
  if (! txn_id_parse(txn_id, data))
    return svn_error_createf(SVN_ERR_FS_MALFORMED_TXN_ID, NULL,
                             "malformed txn id '%s'", data);

  return SVN_NO_ERROR;
}