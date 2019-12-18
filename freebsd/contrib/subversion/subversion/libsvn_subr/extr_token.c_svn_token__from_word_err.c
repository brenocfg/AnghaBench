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
typedef  int /*<<< orphan*/  svn_token_map_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_TOKEN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_TOKEN_UNKNOWN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int svn_token__from_word (int /*<<< orphan*/  const*,char const*) ; 

svn_error_t *
svn_token__from_word_err(int *value,
                         const svn_token_map_t *map,
                         const char *word)
{
  *value = svn_token__from_word(map, word);

  if (*value == SVN_TOKEN_UNKNOWN)
    return svn_error_createf(SVN_ERR_BAD_TOKEN, NULL,
                             _("Token '%s' is unrecognized"),
                             word);

  return SVN_NO_ERROR;
}