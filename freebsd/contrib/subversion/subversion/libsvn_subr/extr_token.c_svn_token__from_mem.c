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
struct TYPE_3__ {char* str; int val; } ;
typedef  TYPE_1__ svn_token_map_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 int SVN_TOKEN_UNKNOWN ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

int
svn_token__from_mem(const svn_token_map_t *map,
                    const char *word,
                    apr_size_t len)
{
  for (; map->str != NULL; ++map)
    if (strncmp(map->str, word, len) == 0 && map->str[len] == '\0')
      return map->val;

  return SVN_TOKEN_UNKNOWN;
}