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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  dba_char_write (char) ; 
 int dba_tell () ; 

int32_t
dba_align(void)
{
	int32_t		 pos;

	pos = dba_tell();
	while (pos & 3) {
		dba_char_write('\0');
		pos++;
	}
	return pos;
}