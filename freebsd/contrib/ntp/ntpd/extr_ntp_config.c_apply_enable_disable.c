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
struct TYPE_7__ {int token; int enabled; } ;
typedef  TYPE_2__ bc_entry ;
typedef  int /*<<< orphan*/  attr_val_fifo ;
struct TYPE_6__ {int i; } ;
struct TYPE_8__ {TYPE_1__ value; struct TYPE_8__* link; } ;
typedef  TYPE_3__ attr_val ;

/* Variables and functions */
 TYPE_3__* HEAD_PFIFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PROTO_AUTHENTICATE ; 
 int /*<<< orphan*/  PROTO_BROADCLIENT ; 
 int /*<<< orphan*/  PROTO_CAL ; 
 int /*<<< orphan*/  PROTO_FILEGEN ; 
 int /*<<< orphan*/  PROTO_KERNEL ; 
 int /*<<< orphan*/  PROTO_MODE7 ; 
 int /*<<< orphan*/  PROTO_MONITOR ; 
 int /*<<< orphan*/  PROTO_NTP ; 
 int /*<<< orphan*/  PROTO_PCEDIGEST ; 
 int /*<<< orphan*/  PROTO_UECRYPTO ; 
 int /*<<< orphan*/  PROTO_UECRYPTONAK ; 
 int /*<<< orphan*/  PROTO_UEDIGEST ; 
#define  T_Auth 140 
#define  T_Bc_bugXXXX 139 
#define  T_Bclient 138 
#define  T_Calibrate 137 
#define  T_Kernel 136 
#define  T_Mode7 135 
#define  T_Monitor 134 
#define  T_Ntp 133 
#define  T_PCEdigest 132 
#define  T_Stats 131 
#define  T_UEcrypto 130 
#define  T_UEcryptonak 129 
#define  T_UEdigest 128 
 TYPE_2__* bc_list ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  proto_config (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
apply_enable_disable(
	attr_val_fifo *	fifo,
	int		enable
	)
{
	attr_val *curr_tok_fifo;
	int option;
#ifdef BC_LIST_FRAMEWORK_NOT_YET_USED
	bc_entry *pentry;
#endif

	for (curr_tok_fifo = HEAD_PFIFO(fifo);
	     curr_tok_fifo != NULL;
	     curr_tok_fifo = curr_tok_fifo->link) {

		option = curr_tok_fifo->value.i;
		switch (option) {

		default:
			msyslog(LOG_ERR,
				"can not apply enable/disable token %d, unknown",
				option);
			break;

		case T_Auth:
			proto_config(PROTO_AUTHENTICATE, enable, 0., NULL);
			break;

		case T_Bclient:
			proto_config(PROTO_BROADCLIENT, enable, 0., NULL);
			break;

		case T_Calibrate:
			proto_config(PROTO_CAL, enable, 0., NULL);
			break;

		case T_Kernel:
			proto_config(PROTO_KERNEL, enable, 0., NULL);
			break;

		case T_Monitor:
			proto_config(PROTO_MONITOR, enable, 0., NULL);
			break;

		case T_Mode7:
			proto_config(PROTO_MODE7, enable, 0., NULL);
			break;

		case T_Ntp:
			proto_config(PROTO_NTP, enable, 0., NULL);
			break;

		case T_PCEdigest:
			proto_config(PROTO_PCEDIGEST, enable, 0., NULL);
			break;

		case T_Stats:
			proto_config(PROTO_FILEGEN, enable, 0., NULL);
			break;

		case T_UEcrypto:
			proto_config(PROTO_UECRYPTO, enable, 0., NULL);
			break;

		case T_UEcryptonak:
			proto_config(PROTO_UECRYPTONAK, enable, 0., NULL);
			break;

		case T_UEdigest:
			proto_config(PROTO_UEDIGEST, enable, 0., NULL);
			break;

#ifdef BC_LIST_FRAMEWORK_NOT_YET_USED
		case T_Bc_bugXXXX:
			pentry = bc_list;
			while (pentry->token) {
				if (pentry->token == option)
					break;
				pentry++;
			}
			if (!pentry->token) {
				msyslog(LOG_ERR,
					"compat token %d not in bc_list[]",
					option);
				continue;
			}
			pentry->enabled = enable;
			break;
#endif
		}
	}
}