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
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_BAD_PROPERTY_VALUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ svn_cstring_casecmp (char*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_handle_warning2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_prop_is_boolean (char const*) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_strip_whitespace (TYPE_1__*) ; 

void
svn_cl__check_boolean_prop_val(const char *propname, const char *propval,
                               apr_pool_t *pool)
{
  svn_stringbuf_t *propbuf;

  if (!svn_prop_is_boolean(propname))
    return;

  propbuf = svn_stringbuf_create(propval, pool);
  svn_stringbuf_strip_whitespace(propbuf);

  if (propbuf->data[0] == '\0'
      || svn_cstring_casecmp(propbuf->data, "0") == 0
      || svn_cstring_casecmp(propbuf->data, "no") == 0
      || svn_cstring_casecmp(propbuf->data, "off") == 0
      || svn_cstring_casecmp(propbuf->data, "false") == 0)
    {
      svn_error_t *err = svn_error_createf
        (SVN_ERR_BAD_PROPERTY_VALUE, NULL,
         _("To turn off the %s property, use 'svn propdel';\n"
           "setting the property to '%s' will not turn it off."),
           propname, propval);
      svn_handle_warning2(stderr, err, "svn: ");
      svn_error_clear(err);
    }
}