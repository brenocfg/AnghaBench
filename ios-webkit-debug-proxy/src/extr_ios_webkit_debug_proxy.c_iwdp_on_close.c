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
typedef  TYPE_1__* iwdp_type_t ;
typedef  TYPE_2__* iwdp_t ;
typedef  int /*<<< orphan*/  iwdp_status ;
typedef  int /*<<< orphan*/  iwdp_iws_t ;
typedef  int /*<<< orphan*/  iwdp_iwi_t ;
typedef  int /*<<< orphan*/  iwdp_iport_t ;
typedef  int /*<<< orphan*/  iwdp_ifs_t ;
typedef  int /*<<< orphan*/  iwdp_idl_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* on_error ) (TYPE_2__*,char*,int) ;} ;
struct TYPE_10__ {int type; } ;

/* Variables and functions */
#define  TYPE_IDL 132 
#define  TYPE_IFS 131 
#define  TYPE_IPORT 130 
#define  TYPE_IWI 129 
#define  TYPE_IWS 128 
 int /*<<< orphan*/  iwdp_idl_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_ifs_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_iport_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_iwi_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwdp_iws_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int) ; 

iwdp_status iwdp_on_close(iwdp_t self, int fd, void *value, bool is_server) {
  int type = ((iwdp_type_t)value)->type;
  switch (type) {
    case TYPE_IDL:
      return iwdp_idl_close(self, (iwdp_idl_t)value);
    case TYPE_IPORT:
      return iwdp_iport_close(self, (iwdp_iport_t)value);
    case TYPE_IWI:
      return iwdp_iwi_close(self, (iwdp_iwi_t)value);
    case TYPE_IWS:
      return iwdp_iws_close(self, (iwdp_iws_t)value);
    case TYPE_IFS:
      return iwdp_ifs_close(self, (iwdp_ifs_t)value);
    default:
      return self->on_error(self, "Unknown close type %d", type);
  }
}