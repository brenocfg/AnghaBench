#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * self_pipe; TYPE_2__* pipeout; TYPE_3__* pipein; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_18__ {int fd; } ;
typedef  TYPE_2__ WSPipeOut ;
struct TYPE_19__ {int fd; } ;
typedef  TYPE_3__ WSPipeIn ;
struct TYPE_20__ {int use_ssl; scalar_t__ sslkey; scalar_t__ sslcert; } ;
struct TYPE_16__ {int /*<<< orphan*/  rfds; int /*<<< orphan*/  wfds; } ;

/* Variables and functions */
#define  EINTR 128 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int MAX (int,int) ; 
 int errno ; 
 TYPE_13__ fdstate ; 
 scalar_t__ initialize_ssl_ctx (TYPE_1__*) ; 
 int max_file_fd ; 
 int /*<<< orphan*/  memset (TYPE_13__*,int /*<<< orphan*/ ,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rfds_wfds (int,TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  ws_fifos (TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ws_listen (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ws_socket (int*) ; 
 TYPE_4__ wsconfig ; 

void
ws_start (WSServer * server)
{
  WSPipeIn *pipein = server->pipein;
  WSPipeOut *pipeout = server->pipeout;
  int listener = 0, conn = 0;

#ifdef HAVE_LIBSSL
  if (wsconfig.sslcert && wsconfig.sslkey) {
    LOG (("==Using TLS/SSL==\n"));
    wsconfig.use_ssl = 1;
    if (initialize_ssl_ctx (server)) {
      LOG (("Unable to initialize_ssl_ctx\n"));
      return;
    }
  }
#endif

  memset (&fdstate, 0, sizeof fdstate);
  ws_socket (&listener);

  while (1) {
    /* If the pipeout file descriptor was opened after the server socket
     * was opened, then it's possible the max file descriptor would be the
     * pipeout fd, in any case we check this here */
    max_file_fd = MAX (listener, pipeout->fd);
    /* Clear out the fd sets for this iteration. */
    FD_ZERO (&fdstate.rfds);
    FD_ZERO (&fdstate.wfds);

    set_rfds_wfds (listener, server, pipein, pipeout);
    max_file_fd += 1;

    /* yep, wait patiently */
    /* should it be using epoll/kqueue? will see... */
    if (select (max_file_fd, &fdstate.rfds, &fdstate.wfds, NULL, NULL) == -1) {
      switch (errno) {
      case EINTR:
        LOG (("A signal was caught on select(2)\n"));
        break;
      default:
        FATAL ("Unable to select: %s.", strerror (errno));
      }
    }
    /* handle self-pipe trick */
    if (FD_ISSET (server->self_pipe[0], &fdstate.rfds)) {
      LOG (("Handled self-pipe to close event loop.\n"));
      break;
    }

    /* iterate over existing connections */
    for (conn = 0; conn < max_file_fd; ++conn) {
      if (conn != pipein->fd && conn != pipeout->fd) {
        ws_listen (listener, conn, server);
      }
    }
    /* handle FIFOs */
    ws_fifos (server, pipein, pipeout);
  }
}