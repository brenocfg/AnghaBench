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

/* Variables and functions */
 char* strsep (char**,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
skip_get_tokens(char *skip_addr, int *sk_addr, int max_index)
{
	char *token;
	int i;

	for (i = 0; i < max_index; i++) {
		token = strsep(&skip_addr, ":");
		if (token == NULL)
			break;
		sk_addr[i] = strtoul(token, 0, 16);
	}
	return (i);
}