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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int8_t ;
typedef  int int16_t ;

/* Variables and functions */
 int MIX_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIX_UNSIGNED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uaudio_mixer_signext(uint8_t type, int val)
{
	if (!MIX_UNSIGNED(type)) {
		if (MIX_SIZE(type) == 2) {
			val = (int16_t)val;
		} else {
			val = (int8_t)val;
		}
	}
	return (val);
}