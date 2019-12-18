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
typedef  char u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 

__attribute__((used)) static u_int8_t getCheckSum(char* data, int len) {
	u_int8_t new = 0;

	if (!data) {
		ERR("Invalid pointer provided!\n");
		return 0;
	}

	for (int i = 0; i < len; i++) {
		new += data[i];
	}

	return new;
}