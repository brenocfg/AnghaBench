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
 int /*<<< orphan*/  FUNC ; 
 void* allocate (int,int /*<<< orphan*/ ) ; 
 char* fmt ; 
 char* fmtend ; 
 char* fp ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void appendstr(char *str) {
	do
		if (fp == fmtend) {
			if (fp) {
				char *s = allocate(2*(fmtend - fmt), FUNC);
				strncpy(s, fmt, fmtend - fmt);
				fp = s + (fmtend - fmt);
				fmtend = s + 2*(fmtend - fmt);
				fmt = s;
			} else {
				fp = fmt = allocate(80, FUNC);
				fmtend = fmt + 80;
			}
		}
	while ((*fp++ = *str++) != 0);
	fp--;
}