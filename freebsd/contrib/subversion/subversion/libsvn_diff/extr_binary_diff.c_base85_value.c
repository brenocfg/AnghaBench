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
 int /*<<< orphan*/  SVN_ERR_DIFF_UNEXPECTED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char const* b85str ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
base85_value(int *value, char c)
{
  const char *p = strchr(b85str, c);
  if (!p)
    return svn_error_create(SVN_ERR_DIFF_UNEXPECTED_DATA, NULL,
                            _("Invalid base85 value"));

  /* It's safe to cast the ptrdiff_t value of the pointer difference
     to int because the value will always be in the range [0..84]. */
  *value = (int)(p - b85str);
  return SVN_NO_ERROR;
}