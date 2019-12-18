#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct termios {char* c_cc; } ;
struct TYPE_7__ {int /*<<< orphan*/  infd; int /*<<< orphan*/  outfd; struct termios attr; scalar_t__ restore_state; int /*<<< orphan*/  noecho; } ;
typedef  TYPE_2__ terminal_handle_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  f; } ;
struct TYPE_8__ {int reqevents; int rtnevents; int /*<<< orphan*/ * p; TYPE_1__ desc; int /*<<< orphan*/  desc_type; } ;
typedef  TYPE_3__ apr_pollfd_t ;

/* Variables and functions */
 int APR_POLLIN ; 
 int /*<<< orphan*/  APR_POLL_FILE ; 
 scalar_t__ APR_STATUS_IS_EINTR (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
#define  EOF 128 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SVN_ERR_CANCELLED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TERMINAL_DEL ; 
 int TERMINAL_EOF ; 
 int TERMINAL_EOL ; 
 int TERMINAL_NONE ; 
 size_t VEOF ; 
 size_t VEOL ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VQUIT ; 
 size_t VSUSP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _cputs (char*) ; 
 int _getch () ; 
 int /*<<< orphan*/  _putch (char) ; 
 scalar_t__ apr_file_getc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_iscntrl (char) ; 
 scalar_t__ apr_poll (TYPE_3__*,int,int*,int) ; 
 int /*<<< orphan*/  echo_control_char (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
terminal_getc(int *code, terminal_handle_t *terminal,
              svn_boolean_t can_erase, apr_pool_t *pool)
{
  const svn_boolean_t echo = !terminal->noecho;
  apr_status_t status = APR_SUCCESS;
  char ch;

#ifdef WIN32
  if (!terminal->infd)
    {
      /* See terminal_open; we're using Console I/O. */

      /*  The following was hoisted from APR's getpass for Windows. */
      int concode = _getch();
      switch (concode)
        {
        case '\r':                      /* end-of-line */
          *code = TERMINAL_EOL;
          if (echo)
            _cputs("\r\n");
          break;

        case EOF:                       /* end-of-file */
        case 26:                        /* Ctrl+Z */
          *code = TERMINAL_EOF;
          if (echo)
            _cputs((concode == EOF ? "[EOF]\r\n" : "^Z\r\n"));
          break;

        case 3:                         /* Ctrl+C, Ctrl+Break */
          /* _getch() bypasses Ctrl+C but not Ctrl+Break detection! */
          if (echo)
            _cputs("^C\r\n");
          return svn_error_create(SVN_ERR_CANCELLED, NULL, NULL);

        case 0:                         /* Function code prefix */
        case 0xE0:
          concode = (concode << 4) | _getch();
          /* Catch {DELETE}, {<--}, Num{DEL} and Num{<--} */
          if (concode == 0xE53 || concode == 0xE4B
              || concode == 0x053 || concode == 0x04B)
            {
              *code = TERMINAL_DEL;
              if (can_erase)
                _cputs("\b \b");
            }
          else
            {
              *code = TERMINAL_NONE;
              _putch('\a');
            }
          break;

        case '\b':                      /* BS */
        case 127:                       /* DEL */
          *code = TERMINAL_DEL;
          if (can_erase)
            _cputs("\b \b");
          break;

        default:
          if (!apr_iscntrl(concode))
            {
              *code = (int)(unsigned char)concode;
              _putch(echo ? concode : '*');
            }
          else
            {
              *code = TERMINAL_NONE;
              _putch('\a');
            }
        }
      return SVN_NO_ERROR;
    }
#elif defined(HAVE_TERMIOS_H)
  if (terminal->restore_state)
    {
      /* We're using a bytewise-immediate termios input */
      const struct termios *const attr = &terminal->attr;

      status = apr_file_getc(&ch, terminal->infd);
      if (status)
        return svn_error_wrap_apr(status, _("Can't read from terminal"));

      if (ch == attr->c_cc[VINTR] || ch == attr->c_cc[VQUIT])
        {
          /* Break */
          echo_control_char(ch, terminal->outfd);
          return svn_error_create(SVN_ERR_CANCELLED, NULL, NULL);
        }
      else if (ch == '\r' || ch == '\n' || ch == attr->c_cc[VEOL])
        {
          /* Newline */
          *code = TERMINAL_EOL;
          apr_file_putc('\n', terminal->outfd);
        }
      else if (ch == '\b' || ch == attr->c_cc[VERASE])
        {
          /* Delete */
          *code = TERMINAL_DEL;
          if (can_erase)
            {
              apr_file_putc('\b', terminal->outfd);
              apr_file_putc(' ', terminal->outfd);
              apr_file_putc('\b', terminal->outfd);
            }
        }
      else if (ch == attr->c_cc[VEOF])
        {
          /* End of input */
          *code = TERMINAL_EOF;
          echo_control_char(ch, terminal->outfd);
        }
      else if (ch == attr->c_cc[VSUSP])
        {
          /* Suspend */
          *code = TERMINAL_NONE;
          kill(0, SIGTSTP);
        }
      else if (!apr_iscntrl(ch))
        {
          /* Normal character */
          *code = (int)(unsigned char)ch;
          apr_file_putc((echo ? ch : '*'), terminal->outfd);
        }
      else
        {
          /* Ignored character */
          *code = TERMINAL_NONE;
          apr_file_putc('\a', terminal->outfd);
        }
      return SVN_NO_ERROR;
    }
#endif /* HAVE_TERMIOS_H */

  /* Fall back to plain stream-based I/O. */
#ifndef WIN32
  /* Wait for input on termin. This code is based on
     apr_wait_for_io_or_timeout().
     Note that this will return an EINTR on a signal. */
  {
    apr_pollfd_t pollset;
    int n;

    pollset.desc_type = APR_POLL_FILE;
    pollset.desc.f = terminal->infd;
    pollset.p = pool;
    pollset.reqevents = APR_POLLIN;

    status = apr_poll(&pollset, 1, &n, -1);

    if (n == 1 && pollset.rtnevents & APR_POLLIN)
      status = APR_SUCCESS;
  }
#endif /* !WIN32 */

  if (!status)
    status = apr_file_getc(&ch, terminal->infd);
  if (APR_STATUS_IS_EINTR(status))
    {
      *code = TERMINAL_NONE;
      return SVN_NO_ERROR;
    }
  else if (APR_STATUS_IS_EOF(status))
    {
      *code = TERMINAL_EOF;
      return SVN_NO_ERROR;
    }
  else if (status)
    return svn_error_wrap_apr(status, _("Can't read from terminal"));

  *code = (int)(unsigned char)ch;
  return SVN_NO_ERROR;
}