#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  self_pipe; int /*<<< orphan*/  pipeout; int /*<<< orphan*/  pipein; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_7__ {char const* host; char const* port; scalar_t__ use_ssl; scalar_t__ strict; int /*<<< orphan*/ * sslkey; int /*<<< orphan*/ * sslcert; int /*<<< orphan*/ * pipeout; int /*<<< orphan*/ * pipein; int /*<<< orphan*/ * origin; int /*<<< orphan*/  max_frm_size; int /*<<< orphan*/ * accesslog; } ;

/* Variables and functions */
 int /*<<< orphan*/  WS_MAX_FRM_SZ ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_wspipein () ; 
 int /*<<< orphan*/  new_wspipeout () ; 
 TYPE_1__* new_wsserver () ; 
 int /*<<< orphan*/  ws_fifo (TYPE_1__*) ; 
 TYPE_2__ wsconfig ; 

WSServer *
ws_init (const char *host, const char *port, void (*initopts) (void))
{
  WSServer *server = new_wsserver ();
  server->pipein = new_wspipein ();
  server->pipeout = new_wspipeout ();
  memset (server->self_pipe, 0, sizeof (server->self_pipe));

  wsconfig.accesslog = NULL;
  wsconfig.host = host;
  wsconfig.max_frm_size = WS_MAX_FRM_SZ;
  wsconfig.origin = NULL;
  wsconfig.pipein = NULL;
  wsconfig.pipeout = NULL;
  wsconfig.sslcert = NULL;
  wsconfig.sslkey = NULL;
  wsconfig.port = port;
  wsconfig.strict = 0;
  wsconfig.use_ssl = 0;

  initopts ();
  ws_fifo (server);

  return server;
}