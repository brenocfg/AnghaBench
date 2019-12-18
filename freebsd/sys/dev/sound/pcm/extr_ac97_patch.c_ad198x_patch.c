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
struct ac97_info {int dummy; } ;

/* Variables and functions */
 int ac97_getsubvendor (struct ac97_info*) ; 
 int ac97_rdcd (struct ac97_info*,int) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int,int) ; 

void ad198x_patch(struct ac97_info* codec)
{
	switch (ac97_getsubvendor(codec)) {
	case 0x11931043:	/* Not for ASUS A9T (probably else too). */
		break;
	default:
		ac97_wrcd(codec, 0x76, ac97_rdcd(codec, 0x76) | 0x0420);
		break;
	}
}