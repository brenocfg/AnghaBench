#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  gcret_t ;
struct TYPE_15__ {int e_event; int /*<<< orphan*/  e_value; } ;
struct TYPE_14__ {TYPE_1__* gp; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* scr_bell ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EVENT ;

/* Variables and functions */
 int EC_QUOTED ; 
#define  E_CHARACTER 133 
#define  E_EOF 132 
#define  E_ERR 131 
#define  E_INTERRUPT 130 
#define  E_REPAINT 129 
#define  E_WRESIZE 128 
 int /*<<< orphan*/  GC_ERR ; 
 int /*<<< orphan*/  GC_FATAL ; 
 int /*<<< orphan*/  GC_INTERRUPT ; 
 int /*<<< orphan*/  GC_OK ; 
 int /*<<< orphan*/  K_VLNEXT ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  v_event_err (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ v_event_get (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vs_repaint (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static gcret_t
v_key(
	SCR *sp,
	int command_events,
	EVENT *evp,
	u_int32_t ec_flags)
{
	u_int32_t quote;

	for (quote = 0;;) {
		if (v_event_get(sp, evp, 0, ec_flags | quote))
			return (GC_FATAL);
		quote = 0;

		switch (evp->e_event) {
		case E_CHARACTER:
			/*
			 * !!!
			 * Historically, ^V was ignored in the command stream,
			 * although it had a useful side-effect of interrupting
			 * mappings.  Adding a quoting bit to the call probably
			 * extends historic practice, but it feels right.
			 */
			if (evp->e_value == K_VLNEXT) {
				quote = EC_QUOTED;
				break;
			}
			return (GC_OK);
		case E_ERR:
		case E_EOF:
			return (GC_FATAL);
		case E_INTERRUPT:
			/*
			 * !!!
			 * Historically, vi beeped on command level interrupts.
			 *
			 * Historically, vi exited to ex mode if no file was
			 * named on the command line, and two interrupts were
			 * generated in a row.  (Just figured you might want
			 * to know that.)
			 */
			(void)sp->gp->scr_bell(sp);
			return (GC_INTERRUPT);
		case E_REPAINT:
			if (vs_repaint(sp, evp))
				return (GC_FATAL);
			break;
		case E_WRESIZE:
			return (GC_ERR);
		default:
			v_event_err(sp, evp);
			return (GC_ERR);
		}
	}
	/* NOTREACHED */
}