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
typedef  int /*<<< orphan*/  terminal_handle_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  terminal_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal_puts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
maybe_print_realm(const char *realm, apr_pool_t *pool)
{
  if (realm)
    {
      terminal_handle_t *terminal;
      SVN_ERR(terminal_open(&terminal, FALSE, pool));
      SVN_ERR(terminal_puts(
                  apr_psprintf(pool,
                               _("Authentication realm: %s\n"), realm),
                  terminal, pool));
      SVN_ERR(terminal_close(terminal));
    }

  return SVN_NO_ERROR;
}