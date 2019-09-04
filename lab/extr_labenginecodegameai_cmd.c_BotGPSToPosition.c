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
typedef  float* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int qtrue ; 

int BotGPSToPosition(char *buf, vec3_t position) {
	int i, j = 0;
	int num, sign;

	for (i = 0; i < 3; i++) {
		num = 0;
		while(buf[j] == ' ') j++;
		if (buf[j] == '-') {
			j++;
			sign = -1;
		}
		else {
			sign = 1;
		}
		while (buf[j]) {
			if (buf[j] >= '0' && buf[j] <= '9') {
				num = num * 10 + buf[j] - '0';
				j++;
			}
			else {
				j++;
				break;
			}
		}
		BotAI_Print(PRT_MESSAGE, "%d\n", sign * num);
		position[i] = (float) sign * num;
	}
	return qtrue;
}