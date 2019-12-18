#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * hEvent; } ;
struct wpa_global_dst {scalar_t__ pipe; struct wpa_global_dst* prev; struct wpa_global_dst* next; TYPE_1__ overlap; struct ctrl_iface_global_priv* priv; } ;
struct ctrl_iface_global_priv {struct wpa_global_dst* ctrl_dst; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ConnectNamedPipe (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateNamedPipe (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
#define  ERROR_IO_PENDING 129 
#define  ERROR_PIPE_CONNECTED 128 
 int FILE_FLAG_OVERLAPPED ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  NAMED_PIPE_PREFIX ; 
 int PIPE_ACCESS_DUPLEX ; 
 int PIPE_READMODE_MESSAGE ; 
 int PIPE_TYPE_MESSAGE ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  REPLY_BUFSIZE ; 
 int /*<<< orphan*/  REQUEST_BUFSIZE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eloop_register_event (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct wpa_global_dst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_close_pipe (struct wpa_global_dst*) ; 
 int /*<<< orphan*/  os_free (struct wpa_global_dst*) ; 
 struct wpa_global_dst* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_global_iface_receive ; 

__attribute__((used)) static int global_open_pipe(struct ctrl_iface_global_priv *priv)
{
	struct wpa_global_dst *dst;
	DWORD err;

	dst = os_zalloc(sizeof(*dst));
	if (dst == NULL)
		return -1;
	wpa_printf(MSG_DEBUG, "CTRL: Open pipe %p", dst);

	dst->priv = priv;
	dst->pipe = INVALID_HANDLE_VALUE;

	dst->overlap.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	if (dst->overlap.hEvent == NULL) {
		wpa_printf(MSG_ERROR, "CTRL: CreateEvent failed: %d",
			   (int) GetLastError());
		goto fail;
	}

	eloop_register_event(dst->overlap.hEvent,
			     sizeof(dst->overlap.hEvent),
			     wpa_supplicant_global_iface_receive, dst, NULL);

	/* TODO: add support for configuring access list for the pipe */
	dst->pipe = CreateNamedPipe(NAMED_PIPE_PREFIX,
				    PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
				    PIPE_TYPE_MESSAGE |
				    PIPE_READMODE_MESSAGE |
				    PIPE_WAIT,
				    10, REPLY_BUFSIZE, REQUEST_BUFSIZE,
				    1000, NULL);
	if (dst->pipe == INVALID_HANDLE_VALUE) {
		wpa_printf(MSG_ERROR, "CTRL: CreateNamedPipe failed: %d",
			   (int) GetLastError());
		goto fail;
	}

	if (ConnectNamedPipe(dst->pipe, &dst->overlap)) {
		wpa_printf(MSG_ERROR, "CTRL: ConnectNamedPipe failed: %d",
			   (int) GetLastError());
		CloseHandle(dst->pipe);
		os_free(dst);
		return -1;
	}

	err = GetLastError();
	switch (err) {
	case ERROR_IO_PENDING:
		wpa_printf(MSG_DEBUG, "CTRL: ConnectNamedPipe: connection in "
			   "progress");
		break;
	case ERROR_PIPE_CONNECTED:
		wpa_printf(MSG_DEBUG, "CTRL: ConnectNamedPipe: already "
			   "connected");
		if (SetEvent(dst->overlap.hEvent))
			break;
		/* fall through */
	default:
		wpa_printf(MSG_DEBUG, "CTRL: ConnectNamedPipe error: %d",
			   (int) err);
		CloseHandle(dst->pipe);
		os_free(dst);
		return -1;
	}

	dst->next = priv->ctrl_dst;
	if (dst->next)
		dst->next->prev = dst;
	priv->ctrl_dst = dst;

	return 0;

fail:
	global_close_pipe(dst);
	return -1;
}