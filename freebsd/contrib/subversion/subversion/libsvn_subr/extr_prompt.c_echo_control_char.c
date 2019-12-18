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
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_file_putc (char const,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_ctype_iscntrl (char) ; 
 scalar_t__ svn_ctype_isprint (char) ; 

__attribute__((used)) static void
echo_control_char(char ch, apr_file_t *outfd)
{
  if (svn_ctype_iscntrl(ch))
    {
      const char substitute = (ch < 32? '@' + ch : '?');
      apr_file_putc('^', outfd);
      apr_file_putc(substitute, outfd);
    }
  else if (svn_ctype_isprint(ch))
    {
      /* Pass printable characters unchanged. */
      apr_file_putc(ch, outfd);
    }
  else
    {
      /* Everything else is strange. */
      apr_file_putc('^', outfd);
      apr_file_putc('!', outfd);
    }
}