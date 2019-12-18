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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* u2s (int /*<<< orphan*/ ,int,int,char*,size_t*) ; 

__attribute__((used)) static char *
x2s(uintmax_t x, bool alt_form, bool uppercase, char *s, size_t *slen_p) {
	s = u2s(x, 16, uppercase, s, slen_p);
	if (alt_form) {
		s -= 2;
		(*slen_p) += 2;
		memcpy(s, uppercase ? "0X" : "0x", 2);
	}
	return s;
}