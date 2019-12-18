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
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * svn_dso_initialize2 () ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 

void
svn_dso_initialize(void)
{
  svn_error_t *err = svn_dso_initialize2();
  if (err)
    {
      svn_error_clear(err);
      abort();
    }
}