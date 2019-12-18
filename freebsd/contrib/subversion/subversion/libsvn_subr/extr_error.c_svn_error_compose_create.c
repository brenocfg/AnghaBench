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
 int /*<<< orphan*/  SVN_ERR_COMPOSED_ERROR ; 
 int /*<<< orphan*/  svn_error_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_error_compose_create(svn_error_t *err1,
                         svn_error_t *err2)
{
  if (err1 && err2)
    {
      svn_error_compose(err1,
                        svn_error_create(SVN_ERR_COMPOSED_ERROR, err2, NULL));
      return err1;
    }
  return err1 ? err1 : err2;
}