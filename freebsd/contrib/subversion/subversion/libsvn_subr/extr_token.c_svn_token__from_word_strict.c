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

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 int SVN_TOKEN_UNKNOWN ; 
 int svn_token__from_word (int /*<<< orphan*/  const*,char const*) ; 

int
svn_token__from_word_strict(const svn_token_map_t *map,
                            const char *word)
{
  int value = svn_token__from_word(map, word);

  if (value == SVN_TOKEN_UNKNOWN)
    SVN_ERR_MALFUNCTION_NO_RETURN();

  return value;
}