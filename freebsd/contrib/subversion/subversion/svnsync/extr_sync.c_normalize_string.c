#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_subst_translate_string2 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
normalize_string(const svn_string_t **str,
                 svn_boolean_t *was_normalized,
                 const char *source_prop_encoding,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_string_t *new_str;

  *was_normalized = FALSE;

  if (*str == NULL)
    return SVN_NO_ERROR;

  SVN_ERR_ASSERT((*str)->data != NULL);

  if (source_prop_encoding == NULL)
    source_prop_encoding = "UTF-8";

  new_str = NULL;
  SVN_ERR(svn_subst_translate_string2(&new_str, NULL, was_normalized,
                                      *str, source_prop_encoding, TRUE,
                                      result_pool, scratch_pool));
  *str = new_str;

  return SVN_NO_ERROR;
}