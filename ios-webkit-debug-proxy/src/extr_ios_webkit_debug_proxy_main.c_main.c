#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sm_t ;
typedef  TYPE_2__* iwdpm_t ;
typedef  TYPE_3__* iwdp_t ;
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_13__ {scalar_t__ (* start ) (TYPE_3__*) ;} ;
struct TYPE_12__ {TYPE_1__* sm; TYPE_3__* iwdp; } ;
struct TYPE_11__ {scalar_t__ (* select ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int iwdpm_configure (TYPE_2__*,int,char**) ; 
 int /*<<< orphan*/  iwdpm_create_bridge (TYPE_2__*) ; 
 int /*<<< orphan*/  iwdpm_free (TYPE_2__*) ; 
 TYPE_2__* iwdpm_new () ; 
 int /*<<< orphan*/  on_signal ; 
 int /*<<< orphan*/  quit_flag ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
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

  iwdpm_t self = iwdpm_new();
  int ret = iwdpm_configure(self, argc, argv);
  if (ret) {
    exit(ret > 0 ? ret : 0);
    return ret;
  }

  iwdpm_create_bridge(self);

  iwdp_t iwdp = self->iwdp;
  if (iwdp->start(iwdp)) {
    return -1;// TODO cleanup
  }

  sm_t sm = self->sm;
  while (!quit_flag) {
    if (sm->select(sm, 2) < 0) {
      ret = -1;
      break;
    }
  }
  sm->cleanup(sm);
  iwdpm_free(self);
#ifdef WIN32
  WSACleanup();
#endif
  return ret;
}