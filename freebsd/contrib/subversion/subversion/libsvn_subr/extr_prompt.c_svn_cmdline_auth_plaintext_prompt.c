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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/ * plaintext_prompt_helper (int /*<<< orphan*/ *,char const*,char const*,char const*,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cmdline_auth_plaintext_prompt(svn_boolean_t *may_save_plaintext,
                                  const char *realmstring,
                                  void *baton,
                                  apr_pool_t *pool)
{
  const char *prompt_string = _("Store password unencrypted (yes/no)? ");
  const char *prompt_text =
  _("\n-----------------------------------------------------------------------"
    "\nATTENTION!  Your password for authentication realm:\n"
    "\n"
    "   %s\n"
    "\n"
    "can only be stored to disk unencrypted!  You are advised to configure\n"
    "your system so that Subversion can store passwords encrypted, if\n"
    "possible.  See the documentation for details.\n"
    "\n"
    "You can avoid future appearances of this warning by setting the value\n"
    "of the 'store-plaintext-passwords' option to either 'yes' or 'no' in\n"
    "'%s'.\n"
    "-----------------------------------------------------------------------\n"
    );

  return plaintext_prompt_helper(may_save_plaintext, realmstring,
                                 prompt_string, prompt_text, baton,
                                 pool);
}