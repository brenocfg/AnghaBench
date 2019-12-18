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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_skel__parse_int(apr_int64_t *n, const svn_skel_t *skel,
                    apr_pool_t *scratch_pool)
{
  const char *str;

  /* We need to duplicate the SKEL contents in order to get a NUL-terminated
     version of it. The SKEL may not have valid memory at DATA[LEN].  */
  str = apr_pstrmemdup(scratch_pool, skel->data, skel->len);
  return svn_error_trace(svn_cstring_atoi64(n, str));
}