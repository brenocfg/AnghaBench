#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_membuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_UTF__UNKNOWN_LENGTH ; 
 int /*<<< orphan*/  decompose_normalized (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ucs4cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_utf__normcmp(int *result,
                 const char *str1, apr_size_t len1,
                 const char *str2, apr_size_t len2,
                 svn_membuf_t *buf1, svn_membuf_t *buf2)
{
  apr_size_t buflen1;
  apr_size_t buflen2;

  /* Shortcut-circuit the decision if at least one of the strings is empty. */
  const svn_boolean_t empty1 =
    (0 == len1 || (len1 == SVN_UTF__UNKNOWN_LENGTH && !*str1));
  const svn_boolean_t empty2 =
    (0 == len2 || (len2 == SVN_UTF__UNKNOWN_LENGTH && !*str2));
  if (empty1 || empty2)
    {
      *result = (empty1 == empty2 ? 0 : (empty1 ? -1 : 1));
      return SVN_NO_ERROR;
    }

  SVN_ERR(decompose_normalized(&buflen1, str1, len1, buf1));
  SVN_ERR(decompose_normalized(&buflen2, str2, len2, buf2));
  *result = ucs4cmp(buf1->data, buflen1, buf2->data, buflen2);
  return SVN_NO_ERROR;
}