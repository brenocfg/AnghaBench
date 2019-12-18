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
typedef  int svn_boolean_t ;
struct TYPE_3__ {char* path; } ;
typedef  TYPE_1__ path_info_t ;
typedef  size_t apr_size_t ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char const*,size_t) ; 

__attribute__((used)) static svn_boolean_t
relevant(path_info_t *pi, const char *prefix, apr_size_t plen)
{
  return (pi && strncmp(pi->path, prefix, plen) == 0 &&
          (!*prefix || pi->path[plen] == '/'));
}