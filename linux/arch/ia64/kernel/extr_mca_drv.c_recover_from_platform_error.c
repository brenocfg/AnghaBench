#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ia64_sal_os_state {int dummy; } ;
typedef  int /*<<< orphan*/  slidx_table_t ;
typedef  int /*<<< orphan*/  peidx_table_t ;
struct TYPE_5__ {scalar_t__ bc; scalar_t__ cc; } ;
typedef  TYPE_1__ pal_processor_state_info_t ;
struct TYPE_6__ {scalar_t__ bsi; int type; scalar_t__ eb; } ;
typedef  TYPE_2__ pal_bus_check_info_t ;

/* Variables and functions */
 scalar_t__ peidx_psp (int /*<<< orphan*/ *) ; 
 int recover_from_read_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,struct ia64_sal_os_state*) ; 

__attribute__((used)) static int
recover_from_platform_error(slidx_table_t *slidx, peidx_table_t *peidx,
			    pal_bus_check_info_t *pbci,
			    struct ia64_sal_os_state *sos)
{
	int status = 0;
	pal_processor_state_info_t *psp =
		(pal_processor_state_info_t*)peidx_psp(peidx);

	if (psp->bc && pbci->eb && pbci->bsi == 0) {
		switch(pbci->type) {
		case 1: /* partial read */
		case 3: /* full line(cpu) read */
		case 9: /* I/O space read */
			status = recover_from_read_error(slidx, peidx, pbci,
							 sos);
			break;
		case 0: /* unknown */
		case 2: /* partial write */
		case 4: /* full line write */
		case 5: /* implicit or explicit write-back operation */
		case 6: /* snoop probe */
		case 7: /* incoming or outgoing ptc.g */
		case 8: /* write coalescing transactions */
		case 10: /* I/O space write */
		case 11: /* inter-processor interrupt message(IPI) */
		case 12: /* interrupt acknowledge or
				external task priority cycle */
		default:
			break;
		}
	} else if (psp->cc && !psp->bc) {	/* Cache error */
		status = recover_from_read_error(slidx, peidx, pbci, sos);
	}

	return status;
}