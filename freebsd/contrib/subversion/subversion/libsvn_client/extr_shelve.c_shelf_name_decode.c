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
 int /*<<< orphan*/  SVN_ERR_BAD_CHANGELIST_NAME ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_1__*,int) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
shelf_name_decode(char **decoded_name_p,
                  const char *codename,
                  apr_pool_t *result_pool)
{
  svn_stringbuf_t *sb
    = svn_stringbuf_create_ensure(strlen(codename) / 2, result_pool);
  const char *input = codename;

  while (*input)
    {
      int c;
      int nchars;
      int nitems = sscanf(input, "%02x%n", &c, &nchars);

      if (nitems != 1 || nchars != 2)
        return svn_error_createf(SVN_ERR_BAD_CHANGELIST_NAME, NULL,
                                 _("Shelve: Bad encoded name '%s'"), codename);
      svn_stringbuf_appendbyte(sb, c);
      input += 2;
    }
  *decoded_name_p = sb->data;
  return SVN_NO_ERROR;
}