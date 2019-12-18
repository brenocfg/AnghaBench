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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ size; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_MIN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_stat (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstring_from_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_io_filesizes_three_different_p(svn_boolean_t *different_p12,
                                   svn_boolean_t *different_p23,
                                   svn_boolean_t *different_p13,
                                   const char *file1,
                                   const char *file2,
                                   const char *file3,
                                   apr_pool_t *scratch_pool)
{
  apr_finfo_t finfo1, finfo2, finfo3;
  apr_status_t status1, status2, status3;
  const char *file1_apr, *file2_apr, *file3_apr;

  /* Not using svn_io_stat() because don't want to generate
     svn_error_t objects for non-error conditions. */

  SVN_ERR(cstring_from_utf8(&file1_apr, file1, scratch_pool));
  SVN_ERR(cstring_from_utf8(&file2_apr, file2, scratch_pool));
  SVN_ERR(cstring_from_utf8(&file3_apr, file3, scratch_pool));

  /* Stat all three files */
  status1 = apr_stat(&finfo1, file1_apr, APR_FINFO_MIN, scratch_pool);
  status2 = apr_stat(&finfo2, file2_apr, APR_FINFO_MIN, scratch_pool);
  status3 = apr_stat(&finfo3, file3_apr, APR_FINFO_MIN, scratch_pool);

  /* If we got an error stat'ing a file, it could be because the
     file was removed... or who knows.  Whatever the case, we
     don't know if the filesizes are definitely different, so
     assume that they're not. */
  *different_p12 = !status1 && !status2 && finfo1.size != finfo2.size;
  *different_p23 = !status2 && !status3 && finfo2.size != finfo3.size;
  *different_p13 = !status1 && !status3 && finfo1.size != finfo3.size;

  return SVN_NO_ERROR;
}