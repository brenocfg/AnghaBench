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
struct TYPE_4__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ svn_membuf_t ;
typedef  int const apr_ssize_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 scalar_t__ SVN_UTF__UNKNOWN_LENGTH ; 
 int UTF8PROC_DECOMPOSE ; 
 int UTF8PROC_NULLTERM ; 
 int UTF8PROC_STABLE ; 
 int /*<<< orphan*/  svn_membuf__ensure (TYPE_1__*,int const) ; 
 int utf8proc_decompose (void const*,scalar_t__,int /*<<< orphan*/ * const,int const,int) ; 

__attribute__((used)) static apr_ssize_t
unicode_decomposition(int transform_flags,
                      const char *string, apr_size_t length,
                      svn_membuf_t *buffer)
{
  const int nullterm = (length == SVN_UTF__UNKNOWN_LENGTH
                        ? UTF8PROC_NULLTERM : 0);

  for (;;)
    {
      apr_int32_t *const ucs4buf = buffer->data;
      const apr_ssize_t ucs4len = buffer->size / sizeof(*ucs4buf);
      const apr_ssize_t result =
        utf8proc_decompose((const void*) string, length, ucs4buf, ucs4len,
                           UTF8PROC_DECOMPOSE | UTF8PROC_STABLE
                           | transform_flags | nullterm);

      if (result < 0 || result <= ucs4len)
        return result;

      /* Increase the decomposition buffer size and retry */
      svn_membuf__ensure(buffer, result * sizeof(*ucs4buf));
    }
}