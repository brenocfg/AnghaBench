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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SVN_KEYWORD_MAX_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ translate_keyword_subst (char*,int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_boolean_t
translate_keyword(char *buf,
                  apr_size_t *len,
                  const char *keyword_name,
                  svn_boolean_t expand,
                  apr_hash_t *keywords)
{
  const svn_string_t *value;

  /* Make sure we gotz good stuffs. */
  assert(*len <= SVN_KEYWORD_MAX_LEN);
  assert((buf[0] == '$') && (buf[*len - 1] == '$'));

  /* Early return for ignored keywords */
  if (! keywords)
    return FALSE;

  value = svn_hash_gets(keywords, keyword_name);

  if (value)
    {
      return translate_keyword_subst(buf, len,
                                     keyword_name, strlen(keyword_name),
                                     expand ? value : NULL);
    }

  return FALSE;
}