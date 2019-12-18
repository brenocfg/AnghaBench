#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* data; int len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int strlen (char const*) ; 

__attribute__((used)) static svn_string_t *
normalize_path(svn_string_t *result,
               const char *path)
{
  apr_size_t len;

  if (path[0] == '/')
    ++path;

  len = strlen(path);
  while (len && path[len-1] == '/')
    --len;

  result->data = path;
  result->len = len;

  return result;
}