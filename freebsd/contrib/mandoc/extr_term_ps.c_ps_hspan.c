#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct termp {TYPE_2__* ps; } ;
struct roffsu {int unit; double scale; } ;
struct TYPE_6__ {TYPE_1__* gly; } ;
struct TYPE_5__ {double lineheight; } ;
struct TYPE_4__ {double wx; } ;

/* Variables and functions */
 double PNT2AFM (struct termp const*,double) ; 
#define  SCALE_BU 136 
#define  SCALE_CM 135 
#define  SCALE_EM 134 
#define  SCALE_EN 133 
#define  SCALE_IN 132 
#define  SCALE_MM 131 
#define  SCALE_PC 130 
#define  SCALE_PT 129 
#define  SCALE_VS 128 
 scalar_t__ TERMFONT_NONE ; 
 TYPE_3__* fonts ; 

__attribute__((used)) static int
ps_hspan(const struct termp *p, const struct roffsu *su)
{
	double		 r;

	/*
	 * All of these measurements are derived by converting from the
	 * native measurement to AFM units.
	 */
	switch (su->unit) {
	case SCALE_BU:
		/*
		 * Traditionally, the default unit is fixed to the
		 * output media.  So this would refer to the point.  In
		 * mandoc(1), however, we stick to the default terminal
		 * scaling unit so that output is the same regardless
		 * the media.
		 */
		r = PNT2AFM(p, su->scale * 72.0 / 240.0);
		break;
	case SCALE_CM:
		r = PNT2AFM(p, su->scale * 72.0 / 2.54);
		break;
	case SCALE_EM:
		r = su->scale *
		    fonts[(int)TERMFONT_NONE].gly[109 - 32].wx;
		break;
	case SCALE_EN:
		r = su->scale *
		    fonts[(int)TERMFONT_NONE].gly[110 - 32].wx;
		break;
	case SCALE_IN:
		r = PNT2AFM(p, su->scale * 72.0);
		break;
	case SCALE_MM:
		r = su->scale *
		    fonts[(int)TERMFONT_NONE].gly[109 - 32].wx / 100.0;
		break;
	case SCALE_PC:
		r = PNT2AFM(p, su->scale * 12.0);
		break;
	case SCALE_PT:
		r = PNT2AFM(p, su->scale * 1.0);
		break;
	case SCALE_VS:
		r = su->scale * p->ps->lineheight;
		break;
	default:
		r = su->scale;
		break;
	}

	return r * 24.0;
}