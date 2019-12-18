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
struct TYPE_3__ {char const* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 

const char *
svn_prop_get_value(const apr_hash_t *props,
                   const char *prop_name)
{
  svn_string_t *str;

  if (!props)
    return NULL;

  str = svn_hash_gets((apr_hash_t *)props, prop_name);

  if (str)
    return str->data;

  return NULL;
}