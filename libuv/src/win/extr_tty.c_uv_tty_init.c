#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ansi_parser_state; scalar_t__ previous_eol; scalar_t__ utf8_codepoint; scalar_t__ utf8_bytes_left; } ;
struct TYPE_8__ {int /*<<< orphan*/  last_input_record; scalar_t__ last_utf16_high_surrogate; scalar_t__ last_key_offset; scalar_t__ last_key_len; int /*<<< orphan*/ * read_raw_wait; int /*<<< orphan*/  read_line_buffer; int /*<<< orphan*/ * unused_; } ;
struct TYPE_10__ {TYPE_3__ wr; TYPE_2__ rd; } ;
struct TYPE_7__ {int fd; } ;
struct TYPE_11__ {int flags; TYPE_4__ tty; scalar_t__ reqs_pending; TYPE_1__ u; scalar_t__ handle; } ;
typedef  TYPE_5__ uv_tty_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int uv_file ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CONSOLE_SCREEN_BUFFER_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_NORMAL ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (scalar_t__,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetNumberOfConsoleInputEvents (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int UV_EBADF ; 
 int UV_HANDLE_BOUND ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_TTY_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 int /*<<< orphan*/  UV_TTY ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__determine_vterm_state (scalar_t__) ; 
 scalar_t__ uv__get_osfhandle (int) ; 
 scalar_t__ uv__need_check_vterm_state ; 
 int /*<<< orphan*/  uv__once_init () ; 
 int /*<<< orphan*/  uv_connection_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_null_buf_ ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tty_capture_initial_style (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_tty_output_lock ; 
 int /*<<< orphan*/  uv_tty_update_virtual_window (int /*<<< orphan*/ *) ; 

int uv_tty_init(uv_loop_t* loop, uv_tty_t* tty, uv_file fd, int unused) {
  BOOL readable;
  DWORD NumberOfEvents;
  HANDLE handle;
  CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
  (void)unused;

  uv__once_init();
  handle = (HANDLE) uv__get_osfhandle(fd);
  if (handle == INVALID_HANDLE_VALUE)
    return UV_EBADF;

  if (fd <= 2) {
    /* In order to avoid closing a stdio file descriptor 0-2, duplicate the
     * underlying OS handle and forget about the original fd.
     * We could also opt to use the original OS handle and just never close it,
     * but then there would be no reliable way to cancel pending read operations
     * upon close.
     */
    if (!DuplicateHandle(INVALID_HANDLE_VALUE,
                         handle,
                         INVALID_HANDLE_VALUE,
                         &handle,
                         0,
                         FALSE,
                         DUPLICATE_SAME_ACCESS))
      return uv_translate_sys_error(GetLastError());
    fd = -1;
  }

  readable = GetNumberOfConsoleInputEvents(handle, &NumberOfEvents);
  if (!readable) {
    /* Obtain the screen buffer info with the output handle. */
    if (!GetConsoleScreenBufferInfo(handle, &screen_buffer_info)) {
      return uv_translate_sys_error(GetLastError());
    }

    /* Obtain the tty_output_lock because the virtual window state is shared
     * between all uv_tty_t handles. */
    uv_sem_wait(&uv_tty_output_lock);

    if (uv__need_check_vterm_state)
      uv__determine_vterm_state(handle);

    /* Remember the original console text attributes. */
    uv_tty_capture_initial_style(&screen_buffer_info);

    uv_tty_update_virtual_window(&screen_buffer_info);

    uv_sem_post(&uv_tty_output_lock);
  }


  uv_stream_init(loop, (uv_stream_t*) tty, UV_TTY);
  uv_connection_init((uv_stream_t*) tty);

  tty->handle = handle;
  tty->u.fd = fd;
  tty->reqs_pending = 0;
  tty->flags |= UV_HANDLE_BOUND;

  if (readable) {
    /* Initialize TTY input specific fields. */
    tty->flags |= UV_HANDLE_TTY_READABLE | UV_HANDLE_READABLE;
    /* TODO: remove me in v2.x. */
    tty->tty.rd.unused_ = NULL;
    tty->tty.rd.read_line_buffer = uv_null_buf_;
    tty->tty.rd.read_raw_wait = NULL;

    /* Init keycode-to-vt100 mapper state. */
    tty->tty.rd.last_key_len = 0;
    tty->tty.rd.last_key_offset = 0;
    tty->tty.rd.last_utf16_high_surrogate = 0;
    memset(&tty->tty.rd.last_input_record, 0, sizeof tty->tty.rd.last_input_record);
  } else {
    /* TTY output specific fields. */
    tty->flags |= UV_HANDLE_WRITABLE;

    /* Init utf8-to-utf16 conversion state. */
    tty->tty.wr.utf8_bytes_left = 0;
    tty->tty.wr.utf8_codepoint = 0;

    /* Initialize eol conversion state */
    tty->tty.wr.previous_eol = 0;

    /* Init ANSI parser state. */
    tty->tty.wr.ansi_parser_state = ANSI_NORMAL;
  }

  return 0;
}