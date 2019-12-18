#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct my_sm_struct {int dummy; } ;
typedef  TYPE_1__* sm_t ;
typedef  TYPE_2__* my_sm_t ;
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_11__ {int port; } ;
struct TYPE_10__ {scalar_t__ (* select ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;int /*<<< orphan*/  (* add_fd ) (TYPE_1__*,int,int /*<<< orphan*/ *,TYPE_2__*,int) ;int /*<<< orphan*/  on_close; int /*<<< orphan*/  on_recv; int /*<<< orphan*/  on_accept; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  on_accept ; 
 int /*<<< orphan*/  on_close ; 
 int /*<<< orphan*/  on_recv ; 
 int /*<<< orphan*/  on_signal ; 
 int /*<<< orphan*/  quit_flag ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_free (TYPE_1__*) ; 
 int sm_listen (int) ; 
 TYPE_1__* sm_new (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

int main(int argc, char** argv) {
  signal(SIGINT, on_signal);
  signal(SIGTERM, on_signal);

#ifdef WIN32
  WSADATA wsa_data;
  int res = WSAStartup(MAKEWORD(2,2), &wsa_data);
  if (res) {
    fprintf(stderr, "WSAStartup failed with error: %d\n", res);
    exit(1);
  }
#endif

  int port = 8080;

  int s_fd = sm_listen(port);
  if (s_fd < 0) {
    return -1;
  }

  sm_t sm = sm_new(4096);
  sm->on_accept = on_accept;
  sm->on_recv = on_recv;
  sm->on_close = on_close;

  my_sm_t my_sm = (my_sm_t)malloc(sizeof(struct my_sm_struct));
  my_sm->port = port;
  //sm->state = my_sm; // optional

  sm->add_fd(sm, s_fd, NULL, my_sm, true);

  int ret = 0;
  while (!quit_flag) {
    if (sm->select(sm, 2) < 0) {
      ret = -1;
      break;
    }
  }
  sm->cleanup(sm);
  free(my_sm);
  sm_free(sm);
#ifdef WIN32
  WSACleanup();
#endif
  return ret;
}