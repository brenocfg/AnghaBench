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
typedef  int u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 

__attribute__((used)) static char *
tohex(const void *_s, size_t l)
{
	u_int8_t *s = (u_int8_t *)_s;
	size_t i, j;
	const char *hex = "0123456789abcdef";
	char *r = malloc((l * 2) + 1);

	assert(r != NULL);
	for (i = j = 0; i < l; i++) {
		r[j++] = hex[(s[i] >> 4) & 0xf];
		r[j++] = hex[s[i] & 0xf];
	}
	r[j] = '\0';
	return r;
}