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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  input ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  svn_cstring_split_append (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

apr_array_header_t *
svn_cstring_split(const char *input,
                  const char *sep_chars,
                  svn_boolean_t chop_whitespace,
                  apr_pool_t *pool)
{
  apr_array_header_t *a = apr_array_make(pool, 5, sizeof(input));
  svn_cstring_split_append(a, input, sep_chars, chop_whitespace, pool);
  return a;
}