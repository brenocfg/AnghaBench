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
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
read_val(const char **result,
          char **buf, const char *end)
{
  const char *start = *buf;

  if (*buf == end)
    return svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
                            _("Unexpected end of entry"));
  if (**buf == '\n')
    {
      (*buf)++;
      *result = NULL;
      return SVN_NO_ERROR;
    }

  while (*buf != end && **buf != '\n')
    (*buf)++;
  if (*buf == end)
    return svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
                            _("Unexpected end of entry"));
  **buf = '\0';
  *result = start;
  (*buf)++;
  return SVN_NO_ERROR;
}