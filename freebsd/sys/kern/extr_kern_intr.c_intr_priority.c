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
typedef  int /*<<< orphan*/  u_char ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;

/* Variables and functions */
#define  INTR_TYPE_AV 134 
#define  INTR_TYPE_BIO 133 
#define  INTR_TYPE_CAM 132 
#define  INTR_TYPE_CLK 131 
#define  INTR_TYPE_MISC 130 
#define  INTR_TYPE_NET 129 
#define  INTR_TYPE_TTY 128 
 int /*<<< orphan*/  PI_AV ; 
 int /*<<< orphan*/  PI_DISK ; 
 int /*<<< orphan*/  PI_DULL ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  PI_REALTIME ; 
 int /*<<< orphan*/  PI_TTY ; 
 int /*<<< orphan*/  panic (char*) ; 

u_char
intr_priority(enum intr_type flags)
{
	u_char pri;

	flags &= (INTR_TYPE_TTY | INTR_TYPE_BIO | INTR_TYPE_NET |
	    INTR_TYPE_CAM | INTR_TYPE_MISC | INTR_TYPE_CLK | INTR_TYPE_AV);
	switch (flags) {
	case INTR_TYPE_TTY:
		pri = PI_TTY;
		break;
	case INTR_TYPE_BIO:
		pri = PI_DISK;
		break;
	case INTR_TYPE_NET:
		pri = PI_NET;
		break;
	case INTR_TYPE_CAM:
		pri = PI_DISK;
		break;
	case INTR_TYPE_AV:
		pri = PI_AV;
		break;
	case INTR_TYPE_CLK:
		pri = PI_REALTIME;
		break;
	case INTR_TYPE_MISC:
		pri = PI_DULL;          /* don't care */
		break;
	default:
		/* We didn't specify an interrupt level. */
		panic("intr_priority: no interrupt type in flags");
	}

	return pri;
}