#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32 ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int flag; int type; int /*<<< orphan*/ * fp; scalar_t__ id_hi; scalar_t__ id_lo; } ;
typedef  TYPE_1__ FILEGEN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int FGEN_FLAG_ENABLED ; 
#define  FILEGEN_AGE 134 
#define  FILEGEN_DAY 133 
#define  FILEGEN_MONTH 132 
#define  FILEGEN_NONE 131 
#define  FILEGEN_PID 130 
#define  FILEGEN_WEEK 129 
#define  FILEGEN_YEAR 128 
 int TRUE ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filegen_open (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int getpid () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
filegen_setup(
	FILEGEN *	gen,
	u_int32		now
	)
{
	int	current;
	time_t	pivot;

	if (!(gen->flag & FGEN_FLAG_ENABLED)) {
		if (NULL != gen->fp) {
			fclose(gen->fp);
			gen->fp = NULL;
		}
		return;
	}

	switch (gen->type) {

	default:
	case FILEGEN_NONE:
		current = TRUE;
		break;

	case FILEGEN_PID:
		current = ((int)gen->id_lo == getpid());
		break;

	case FILEGEN_AGE:
		current = (gen->id_lo <= current_time) &&
			  (gen->id_hi > current_time);
		break;

	case FILEGEN_DAY:
	case FILEGEN_WEEK:
	case FILEGEN_MONTH:
	case FILEGEN_YEAR:
		current = (gen->id_lo <= now) &&
			  (gen->id_hi > now);
		break;
	}
	/*
	 * try to open file if not yet open
	 * reopen new file generation file on change of generation id
	 */
	if (NULL == gen->fp || !current) {
		DPRINTF(1, ("filegen  %0x %u\n", gen->type, now));
		pivot = time(NULL);
		filegen_open(gen, now, &pivot);
	}
}