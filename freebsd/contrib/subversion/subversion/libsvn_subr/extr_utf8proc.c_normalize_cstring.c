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
typedef  int apr_ssize_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_UTF8PROC_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int UTF8PROC_CASEFOLD ; 
 int UTF8PROC_COMPOSE ; 
 int UTF8PROC_STABLE ; 
 int UTF8PROC_STRIPMARK ; 
 int /*<<< orphan*/  gettext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_membuf__resize (TYPE_1__*,int) ; 
 int unicode_decomposition (int,char const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  utf8proc_errmsg (int) ; 
 int utf8proc_reencode (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static svn_error_t *
normalize_cstring(apr_size_t *result_length,
                  const char *string, apr_size_t length,
                  svn_boolean_t casefold,
                  svn_boolean_t stripmark,
                  svn_membuf_t *buffer)
{
  int flags = 0;
  apr_ssize_t result;

  if (casefold)
    flags |= UTF8PROC_CASEFOLD;

  if (stripmark)
    flags |= UTF8PROC_STRIPMARK;

  result = unicode_decomposition(flags, string, length, buffer);
  if (result >= 0)
    {
      svn_membuf__resize(buffer, result * sizeof(apr_int32_t) + 1);
      result = utf8proc_reencode(buffer->data, result,
                                 UTF8PROC_COMPOSE | UTF8PROC_STABLE);
    }
  if (result < 0)
    return svn_error_create(SVN_ERR_UTF8PROC_ERROR, NULL,
                            gettext(utf8proc_errmsg(result)));
  *result_length = result;
  return SVN_NO_ERROR;
}