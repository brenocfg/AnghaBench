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
struct utsname {char* release; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  bsdcompat ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 

__attribute__((used)) static void
clear_bsdcompat(void) {
#ifdef __linux__
	 struct utsname buf;
	 char *endp;
	 long int major;
	 long int minor;

	 uname(&buf);    /* Can only fail if buf is bad in Linux. */

	 /* Paranoia in parsing can be increased, but we trust uname(). */
	 major = strtol(buf.release, &endp, 10);
	 if (*endp == '.') {
		minor = strtol(endp+1, &endp, 10);
		if ((major > 2) || ((major == 2) && (minor >= 4))) {
			bsdcompat = ISC_FALSE;
		}
	 }
#endif /* __linux __ */
}