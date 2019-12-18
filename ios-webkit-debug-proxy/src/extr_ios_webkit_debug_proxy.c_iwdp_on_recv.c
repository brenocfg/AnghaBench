#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_2__* ws_t ;
typedef  TYPE_3__* wi_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  TYPE_4__* iwdp_type_t ;
typedef  TYPE_5__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  TYPE_6__* iwdp_iws_t ;
typedef  TYPE_7__* iwdp_iwi_t ;
typedef  TYPE_8__* iwdp_ifs_t ;
typedef  TYPE_9__* iwdp_idl_t ;
typedef  TYPE_10__* dl_t ;
struct TYPE_27__ {TYPE_10__* dl; } ;
struct TYPE_26__ {TYPE_1__* iws; } ;
struct TYPE_25__ {TYPE_3__* wi; } ;
struct TYPE_24__ {TYPE_2__* ws; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* on_error ) (TYPE_5__*,char*,int) ;int /*<<< orphan*/  (* remove_fd ) (TYPE_5__*,int) ;int /*<<< orphan*/  (* send ) (TYPE_5__*,int,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {int type; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* on_recv ) (TYPE_3__*,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  (* on_recv ) (TYPE_2__*,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {int ws_fd; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* on_recv ) (TYPE_10__*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  TYPE_IDL 131 
#define  TYPE_IFS 130 
#define  TYPE_IWI 129 
#define  TYPE_IWS 128 
 int /*<<< orphan*/  stub1 (TYPE_10__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_5__*,char*,int) ; 

iwdp_status iwdp_on_recv(iwdp_t self, int fd, void *value,
    const char *buf, ssize_t length) {
  int type = ((iwdp_type_t)value)->type;
  switch (type) {
    case TYPE_IDL:
      {
        dl_t dl = ((iwdp_idl_t)value)->dl;
        return dl->on_recv(dl, buf, length);
      }
    case TYPE_IWI:
      {
        wi_t wi = ((iwdp_iwi_t)value)->wi;
        return wi->on_recv(wi, buf, length);
      }
    case TYPE_IWS:
      {
        ws_t ws = ((iwdp_iws_t)value)->ws;
        return ws->on_recv(ws, buf, length);
      }
    case TYPE_IFS:
      {
        int ws_fd = ((iwdp_ifs_t)value)->iws->ws_fd;
        iwdp_status ret = self->send(self, ws_fd, buf, length);
        if (ret) {
          self->remove_fd(self, ws_fd);
        }
        return ret;
      }
    default:
      return self->on_error(self, "Unexpected recv type %d", type);
  }
}