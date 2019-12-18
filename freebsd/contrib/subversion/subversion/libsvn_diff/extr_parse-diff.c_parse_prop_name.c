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
struct TYPE_4__ {char const* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int strlen (char const*) ; 
 scalar_t__ svn_prop_name_is_valid (char const*) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_utf_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
parse_prop_name(const char **prop_name, const char *header,
                const char *indicator, apr_pool_t *result_pool)
{
  SVN_ERR(svn_utf_cstring_to_utf8(prop_name,
                                  header + strlen(indicator),
                                  result_pool));
  if (**prop_name == '\0')
    *prop_name = NULL;
  else if (! svn_prop_name_is_valid(*prop_name))
    {
      svn_stringbuf_t *buf = svn_stringbuf_create(*prop_name, result_pool);
      svn_stringbuf_strip_whitespace(buf);
      *prop_name = (svn_prop_name_is_valid(buf->data) ? buf->data : NULL);
    }

  return SVN_NO_ERROR;
}