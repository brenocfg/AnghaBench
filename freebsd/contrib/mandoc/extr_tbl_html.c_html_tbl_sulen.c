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
struct roffsu {double scale; int unit; } ;

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

__attribute__((used)) static size_t
html_tbl_sulen(const struct roffsu *su, void *arg)
{
	if (su->scale < 0.0)
		return 0;

	switch (su->unit) {
	case SCALE_FS:  /* 2^16 basic units */
		return su->scale * 65536.0 / 24.0;
	case SCALE_IN:  /* 10 characters per inch */
		return su->scale * 10.0;
	case SCALE_CM:  /* 2.54 cm per inch */
		return su->scale * 10.0 / 2.54;
	case SCALE_PC:  /* 6 pica per inch */
	case SCALE_VS:
		return su->scale * 10.0 / 6.0;
	case SCALE_EN:
	case SCALE_EM:
		return su->scale;
	case SCALE_PT:  /* 12 points per pica */
		return su->scale * 10.0 / 6.0 / 12.0;
	case SCALE_BU:  /* 24 basic units per character */
		return su->scale / 24.0;
	case SCALE_MM:  /* 1/1000 inch */
		return su->scale / 100.0;
	default:
		abort();
	}
}