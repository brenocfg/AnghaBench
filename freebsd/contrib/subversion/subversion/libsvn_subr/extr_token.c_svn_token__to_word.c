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
struct TYPE_3__ {char const* str; int val; } ;
typedef  TYPE_1__ svn_token_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 

const char *
svn_token__to_word(const svn_token_map_t *map,
                   int value)
{
  for (; map->str != NULL; ++map)
    if (map->val == value)
      return map->str;

  /* Internal, numeric values should always be found.  */
  SVN_ERR_MALFUNCTION_NO_RETURN();
}