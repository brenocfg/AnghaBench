#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct libworker {int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  UB_LIBCMD_ANSWER 131 
#define  UB_LIBCMD_CANCEL 130 
#define  UB_LIBCMD_NEWQUERY 129 
#define  UB_LIBCMD_QUIT 128 
 int /*<<< orphan*/  comm_base_exit (int /*<<< orphan*/ ) ; 
 int context_serial_getcmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_cancel (struct libworker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_newq (struct libworker*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,int) ; 

__attribute__((used)) static void
libworker_do_cmd(struct libworker* w, uint8_t* msg, uint32_t len)
{
	switch(context_serial_getcmd(msg, len)) {
		default:
		case UB_LIBCMD_ANSWER:
			log_err("unknown command for bg worker %d", 
				(int)context_serial_getcmd(msg, len));
			/* and fall through to quit */
			/* fallthrough */
		case UB_LIBCMD_QUIT:
			free(msg);
			comm_base_exit(w->base);
			break;
		case UB_LIBCMD_NEWQUERY:
			handle_newq(w, msg, len);
			break;
		case UB_LIBCMD_CANCEL:
			handle_cancel(w, msg, len);
			break;
	}
}