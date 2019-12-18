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
 scalar_t__ tolower (unsigned char) ; 

__attribute__((used)) static void
ldns_tolower_str(char* s)
{
	if(s) {
		while(*s) {
			*s = (char)tolower((unsigned char)*s);
			s++;
		}
	}
}