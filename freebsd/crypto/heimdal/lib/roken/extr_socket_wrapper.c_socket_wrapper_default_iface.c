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
 unsigned int MAX_WRAPPED_INTERFACES ; 
 char* getenv (char*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static unsigned int socket_wrapper_default_iface(void)
{
	const char *s = getenv("SOCKET_WRAPPER_DEFAULT_IFACE");
	if (s) {
		unsigned int iface;
		if (sscanf(s, "%u", &iface) == 1) {
			if (iface >= 1 && iface <= MAX_WRAPPED_INTERFACES) {
				return iface;
			}
		}
	}

	return 1;/* 127.0.0.1 */
}