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
 scalar_t__ Q_IsColorString (char*) ; 

void RemoveColorEscapeSequences( char *text ) {
	int i, l;

	l = 0;
	for ( i = 0; text[i]; i++ ) {
		if (Q_IsColorString(&text[i])) {
			i++;
			continue;
		}
		if (text[i] > 0x7E)
			continue;
		text[l++] = text[i];
	}
	text[l] = '\0';
}