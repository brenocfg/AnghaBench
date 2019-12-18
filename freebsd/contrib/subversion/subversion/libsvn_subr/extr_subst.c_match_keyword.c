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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static svn_boolean_t
match_keyword(char *buf,
              apr_size_t len,
              char *keyword_name,
              apr_hash_t *keywords)
{
  apr_size_t i;

  /* Early return for ignored keywords */
  if (! keywords)
    return FALSE;

  /* Extract the name of the keyword */
  for (i = 0; i < len - 2 && buf[i + 1] != ':'; i++)
    keyword_name[i] = buf[i + 1];
  keyword_name[i] = '\0';

  return svn_hash_gets(keywords, keyword_name) != NULL;
}