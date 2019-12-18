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
 int EOF ; 
 int /*<<< orphan*/  assert (int) ; 
 int gpbc () ; 
 int /*<<< orphan*/  pushback (char const) ; 

__attribute__((used)) static int
do_look_ahead(int t, const char *token)
{
	int i;

	assert((unsigned char)t == (unsigned char)token[0]);

	for (i = 1; *++token; i++) {
		t = gpbc();
		if (t == EOF || (unsigned char)t != (unsigned char)*token) {
			pushback(t);
			while (--i)
				pushback(*--token);
			return 0;
		}
	}
	return 1;
}