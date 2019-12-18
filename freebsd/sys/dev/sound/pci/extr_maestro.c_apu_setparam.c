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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
typedef  int u_int ;
struct agg_info {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  APUREG_AMPLITUDE ; 
 int /*<<< orphan*/  APUREG_CURPTR ; 
 int /*<<< orphan*/  APUREG_ENDPTR ; 
 int /*<<< orphan*/  APUREG_FREQ_HIWORD ; 
 int /*<<< orphan*/  APUREG_FREQ_LOBYTE ; 
 int /*<<< orphan*/  APUREG_LOOPLEN ; 
 int /*<<< orphan*/  APUREG_POSITION ; 
 int /*<<< orphan*/  APUREG_ROUTING ; 
 int /*<<< orphan*/  APUREG_WAVESPACE ; 
 int APU_64KPAGE_MASK ; 
 int APU_FREQ_LOBYTE_SHIFT ; 
 int APU_PAN_MASK ; 
 int APU_PAN_SHIFT ; 
 int APU_RADIUS_MASK ; 
 int APU_RADIUS_SHIFT ; 
 int APU_plus6dB ; 
 int PAN_FRONT ; 
 int RADIUS_CENTERCIRCLE ; 
 int /*<<< orphan*/  wp_wrapu (struct agg_info*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
apu_setparam(struct agg_info *ess, int apuch,
    u_int32_t wpwa, u_int16_t size, int16_t pan, u_int dv)
{
	wp_wrapu(ess, apuch, APUREG_WAVESPACE, (wpwa >> 8) & APU_64KPAGE_MASK);
	wp_wrapu(ess, apuch, APUREG_CURPTR, wpwa);
	wp_wrapu(ess, apuch, APUREG_ENDPTR, wpwa + size);
	wp_wrapu(ess, apuch, APUREG_LOOPLEN, size);
	wp_wrapu(ess, apuch, APUREG_ROUTING, 0);
	wp_wrapu(ess, apuch, APUREG_AMPLITUDE, 0xf000);
	wp_wrapu(ess, apuch, APUREG_POSITION, 0x8f00
	    | (APU_RADIUS_MASK & (RADIUS_CENTERCIRCLE << APU_RADIUS_SHIFT))
	    | (APU_PAN_MASK & ((pan + PAN_FRONT) << APU_PAN_SHIFT)));
	wp_wrapu(ess, apuch, APUREG_FREQ_LOBYTE,
	    APU_plus6dB | ((dv & 0xff) << APU_FREQ_LOBYTE_SHIFT));
	wp_wrapu(ess, apuch, APUREG_FREQ_HIWORD, dv >> 8);
}