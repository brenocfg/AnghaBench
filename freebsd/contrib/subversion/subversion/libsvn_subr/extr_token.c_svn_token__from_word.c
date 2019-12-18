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
struct TYPE_3__ {int val; int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ svn_token_map_t ;

/* Variables and functions */
 int SVN_TOKEN_UNKNOWN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

int
svn_token__from_word(const svn_token_map_t *map,
                     const char *word)
{
  if (word == NULL)
    return SVN_TOKEN_UNKNOWN;

  for (; map->str != NULL; ++map)
    if (strcmp(map->str, word) == 0)
      return map->val;

  return SVN_TOKEN_UNKNOWN;
}