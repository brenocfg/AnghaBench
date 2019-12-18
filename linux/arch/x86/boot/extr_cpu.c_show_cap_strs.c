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
typedef  int u32 ;

/* Variables and functions */
 int NCAPINTS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ x86_cap_strs ; 

__attribute__((used)) static void show_cap_strs(u32 *err_flags)
{
	int i, j;
#ifdef CONFIG_X86_FEATURE_NAMES
	const unsigned char *msg_strs = (const unsigned char *)x86_cap_strs;
	for (i = 0; i < NCAPINTS; i++) {
		u32 e = err_flags[i];
		for (j = 0; j < 32; j++) {
			if (msg_strs[0] < i ||
			    (msg_strs[0] == i && msg_strs[1] < j)) {
				/* Skip to the next string */
				msg_strs += 2;
				while (*msg_strs++)
					;
			}
			if (e & 1) {
				if (msg_strs[0] == i &&
				    msg_strs[1] == j &&
				    msg_strs[2])
					printf("%s ", msg_strs+2);
				else
					printf("%d:%d ", i, j);
			}
			e >>= 1;
		}
	}
#else
	for (i = 0; i < NCAPINTS; i++) {
		u32 e = err_flags[i];
		for (j = 0; j < 32; j++) {
			if (e & 1)
				printf("%d:%d ", i, j);
			e >>= 1;
		}
	}
#endif
}