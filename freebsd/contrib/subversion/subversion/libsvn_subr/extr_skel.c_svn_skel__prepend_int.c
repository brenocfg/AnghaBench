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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INT64_BUFFER_SIZE ; 
 char* apr_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn__i64toa (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void svn_skel__prepend_int(apr_int64_t value,
                           svn_skel_t *skel,
                           apr_pool_t *result_pool)
{
  char *val_string = apr_palloc(result_pool, SVN_INT64_BUFFER_SIZE);
  svn__i64toa(val_string, value);

  svn_skel__prepend_str(val_string, skel, result_pool);
}