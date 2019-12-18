#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int SVN_INT64_BUFFER_SIZE ; 
 char const* apr_pstrmemdup (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  svn__i64toa (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 

const char *
svn_fs_fs__id_txn_unparse(const svn_fs_fs__id_part_t *txn_id,
                          apr_pool_t *pool)
{
  char string[2 * SVN_INT64_BUFFER_SIZE + 1];
  char *p = string;

  p += svn__i64toa(p, txn_id->revision);
  *(p++) = '-';
  p += svn__ui64tobase36(p, txn_id->number);

  return apr_pstrmemdup(pool, string, p - string);
}