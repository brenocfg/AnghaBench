#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fg; int bg; } ;
struct TYPE_8__ {int fg; int bg; } ;
struct TYPE_10__ {int flags; int saved_xpos; int saved_ypos; void* cur_attr; TYPE_2__ std_color; TYPE_2__ cur_color; TYPE_1__ dflt_rev_color; TYPE_1__ rev_color; TYPE_2__ dflt_std_color; int /*<<< orphan*/  esc; int /*<<< orphan*/  attr_mask; } ;
typedef  TYPE_3__ term_stat ;
typedef  int /*<<< orphan*/  scr_stat ;
struct TYPE_12__ {int flags; } ;
struct TYPE_11__ {int /*<<< orphan*/  te_refcount; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NORMAL_ATTR ; 
 int SCTERM_BUSY ; 
 int SC_NORM_ATTR ; 
 int SC_NORM_REV_ATTR ; 
#define  SC_TE_COLD_INIT 129 
#define  SC_TE_WARM_INIT 128 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 void* mask2attr (TYPE_3__*) ; 
 TYPE_5__ reserved_term_stat ; 
 TYPE_4__ sc_term_sc ; 

__attribute__((used)) static int
scterm_init(scr_stat *scp, void **softc, int code)
{
	term_stat *tcp;

	if (*softc == NULL) {
		if (reserved_term_stat.flags & SCTERM_BUSY)
			return EINVAL;
		*softc = &reserved_term_stat;
	}
	tcp = *softc;

	switch (code) {
	case SC_TE_COLD_INIT:
		bzero(tcp, sizeof(*tcp));
		tcp->flags = SCTERM_BUSY;
		tcp->esc = 0;
		tcp->saved_xpos = -1;
		tcp->saved_ypos = -1;
		tcp->attr_mask = NORMAL_ATTR;
		/* XXX */
		tcp->dflt_std_color.fg = SC_NORM_ATTR & 0x0f;
		tcp->dflt_std_color.bg = (SC_NORM_ATTR >> 4) & 0x0f;
		tcp->dflt_rev_color.fg = SC_NORM_REV_ATTR & 0x0f;
		tcp->dflt_rev_color.bg = (SC_NORM_REV_ATTR >> 4) & 0x0f;
		tcp->std_color = tcp->dflt_std_color;
		tcp->rev_color = tcp->dflt_rev_color;
		tcp->cur_color = tcp->std_color;
		tcp->cur_attr = mask2attr(tcp);
		++sc_term_sc.te_refcount;
		break;

	case SC_TE_WARM_INIT:
		tcp->esc = 0;
		tcp->saved_xpos = -1;
		tcp->saved_ypos = -1;
#if 0
		tcp->std_color = tcp->dflt_std_color;
		tcp->rev_color = tcp->dflt_rev_color;
#endif
		tcp->cur_color = tcp->std_color;
		tcp->cur_attr = mask2attr(tcp);
		break;
	}

	return 0;
}