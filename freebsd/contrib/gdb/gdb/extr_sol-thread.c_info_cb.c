#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ti_type; int ti_state; scalar_t__ ti_startfunc; scalar_t__ ti_pc; int /*<<< orphan*/  ti_lid; int /*<<< orphan*/  ti_tid; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  int /*<<< orphan*/  td_err_e ;
struct minimal_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 int /*<<< orphan*/  TD_OK ; 
#define  TD_THR_ACTIVE 134 
#define  TD_THR_RUN 133 
#define  TD_THR_SLEEP 132 
#define  TD_THR_STOPPED 131 
#define  TD_THR_STOPPED_ASLEEP 130 
 scalar_t__ TD_THR_SYSTEM ; 
#define  TD_THR_UNKNOWN 129 
#define  TD_THR_ZOMBIE 128 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (scalar_t__) ; 
 int /*<<< orphan*/  p_td_thr_get_info (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  paddr (scalar_t__) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int
info_cb (const td_thrhandle_t *th, void *s)
{
  td_err_e ret;
  td_thrinfo_t ti;

  if ((ret = p_td_thr_get_info (th, &ti)) == TD_OK)
    {
      printf_filtered ("%s thread #%d, lwp %d, ",
		       ti.ti_type == TD_THR_SYSTEM ? "system" : "user  ",
		       ti.ti_tid, ti.ti_lid);
      switch (ti.ti_state)
	{
	default:
	case TD_THR_UNKNOWN:
	  printf_filtered ("<unknown state>");
	  break;
	case TD_THR_STOPPED:
	  printf_filtered ("(stopped)");
	  break;
	case TD_THR_RUN:
	  printf_filtered ("(run)    ");
	  break;
	case TD_THR_ACTIVE:
	  printf_filtered ("(active) ");
	  break;
	case TD_THR_ZOMBIE:
	  printf_filtered ("(zombie) ");
	  break;
	case TD_THR_SLEEP:
	  printf_filtered ("(asleep) ");
	  break;
	case TD_THR_STOPPED_ASLEEP:
	  printf_filtered ("(stopped asleep)");
	  break;
	}
      /* Print thr_create start function: */
      if (ti.ti_startfunc != 0)
	{
	  struct minimal_symbol *msym;
	  msym = lookup_minimal_symbol_by_pc (ti.ti_startfunc);
	  if (msym)
	    printf_filtered ("   startfunc: %s\n", DEPRECATED_SYMBOL_NAME (msym));
	  else
	    printf_filtered ("   startfunc: 0x%s\n", paddr (ti.ti_startfunc));
	}

      /* If thread is asleep, print function that went to sleep: */
      if (ti.ti_state == TD_THR_SLEEP)
	{
	  struct minimal_symbol *msym;
	  msym = lookup_minimal_symbol_by_pc (ti.ti_pc);
	  if (msym)
	    printf_filtered (" - Sleep func: %s\n", DEPRECATED_SYMBOL_NAME (msym));
	  else
	    printf_filtered (" - Sleep func: 0x%s\n", paddr (ti.ti_startfunc));
	}

      /* Wrap up line, if necessary */
      if (ti.ti_state != TD_THR_SLEEP && ti.ti_startfunc == 0)
	printf_filtered ("\n");	/* don't you hate counting newlines? */
    }
  else
    warning ("info sol-thread: failed to get info for thread.");

  return 0;
}