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
struct termp {int dummy; } ;
struct roffsu {int unit; double scale; } ;

/* Variables and functions */
#define  SCALE_BU 137 
#define  SCALE_CM 136 
#define  SCALE_EM 135 
#define  SCALE_EN 134 
#define  SCALE_FS 133 
#define  SCALE_IN 132 
#define  SCALE_MM 131 
#define  SCALE_PC 130 
#define  SCALE_PT 129 
#define  SCALE_VS 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static int
ascii_hspan(const struct termp *p, const struct roffsu *su)
{
	double		 r;

	switch (su->unit) {
	case SCALE_BU:
		r = su->scale;
		break;
	case SCALE_CM:
		r = su->scale * 240.0 / 2.54;
		break;
	case SCALE_FS:
		r = su->scale * 65536.0;
		break;
	case SCALE_IN:
		r = su->scale * 240.0;
		break;
	case SCALE_MM:
		r = su->scale * 0.24;
		break;
	case SCALE_VS:
	case SCALE_PC:
		r = su->scale * 40.0;
		break;
	case SCALE_PT:
		r = su->scale * 10.0 / 3.0;
		break;
	case SCALE_EN:
	case SCALE_EM:
		r = su->scale * 24.0;
		break;
	default:
		abort();
	}
	return r > 0.0 ? r + 0.01 : r - 0.01;
}