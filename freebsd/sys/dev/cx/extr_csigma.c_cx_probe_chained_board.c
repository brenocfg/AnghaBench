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
typedef  int /*<<< orphan*/  port_t ;

/* Variables and functions */
 scalar_t__ BSR (int /*<<< orphan*/ ) ; 
#define  BSR_OSC_18432 144 
#define  BSR_OSC_20 143 
 int BSR_OSC_MASK ; 
 int BSR_REV_MASK ; 
 int BSR_VAR_MASK ; 
#define  CRONYX_100 142 
#define  CRONYX_400 141 
#define  CRONYX_401 140 
#define  CRONYX_401s 139 
#define  CRONYX_404 138 
#define  CRONYX_410 137 
#define  CRONYX_410s 136 
#define  CRONYX_440 135 
#define  CRONYX_500 134 
#define  CRONYX_703 133 
#define  CRONYX_801 132 
#define  CRONYX_801s 131 
#define  CRONYX_810 130 
#define  CRONYX_810s 129 
#define  CRONYX_840 128 
 int inb (scalar_t__) ; 

__attribute__((used)) static int cx_probe_chained_board (port_t port, int *c0, int *c1)
{
	int rev, i;

	/* Read and check the board revision code. */
	rev = inb (BSR(port));
	*c0 = *c1 = 0;
	switch (rev & BSR_VAR_MASK) {
	case CRONYX_100:	*c0 = 1;	break;
	case CRONYX_400:	*c1 = 1;	break;
	case CRONYX_500:	*c0 = *c1 = 1;	break;
	case CRONYX_410:	*c0 = 1;	break;
	case CRONYX_810:	*c0 = *c1 = 1;	break;
	case CRONYX_410s:	*c0 = 1;	break;
	case CRONYX_810s:	*c0 = *c1 = 1;	break;
	case CRONYX_440:	*c0 = 1;	break;
	case CRONYX_840:	*c0 = *c1 = 1;	break;
	case CRONYX_401:	*c0 = 1;	break;
	case CRONYX_801:	*c0 = *c1 = 1;	break;
	case CRONYX_401s:	*c0 = 1;	break;
	case CRONYX_801s:	*c0 = *c1 = 1;	break;
	case CRONYX_404:	*c0 = 1;	break;
	case CRONYX_703:	*c0 = *c1 = 1;	break;
	default:		return (0);	/* invalid variant code */
	}

	switch (rev & BSR_OSC_MASK) {
	case BSR_OSC_20:	/* 20 MHz */
	case BSR_OSC_18432:	/* 18.432 MHz */
		break;
	default:
		return (0);	/* oscillator frequency does not match */
	}

	for (i=2; i<0x10; i+=2)
		if ((inb (BSR(port)+i) & BSR_REV_MASK) != (rev & BSR_REV_MASK))
			return (0);	/* status changed? */
	return (1);
}