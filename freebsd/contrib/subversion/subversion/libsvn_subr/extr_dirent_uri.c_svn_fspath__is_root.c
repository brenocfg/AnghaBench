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
typedef  int svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */

svn_boolean_t
svn_fspath__is_root(const char *fspath, apr_size_t len)
{
  /* directory is root if it's equal to '/' */
  return (len == 1 && fspath[0] == '/');
}