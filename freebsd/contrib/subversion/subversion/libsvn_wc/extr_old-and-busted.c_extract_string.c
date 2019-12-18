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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 char const* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const char *
extract_string(apr_hash_t *atts,
               const char *att_name,
               apr_pool_t *result_pool)
{
  const char *value = svn_hash_gets(atts, att_name);

  if (value == NULL)
    return NULL;

  return apr_pstrdup(result_pool, value);
}