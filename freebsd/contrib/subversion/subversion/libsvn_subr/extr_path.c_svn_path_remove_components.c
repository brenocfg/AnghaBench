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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_path_remove_component (int /*<<< orphan*/ *) ; 

void
svn_path_remove_components(svn_stringbuf_t *path, apr_size_t n)
{
  while (n > 0)
    {
      svn_path_remove_component(path);
      n--;
    }
}