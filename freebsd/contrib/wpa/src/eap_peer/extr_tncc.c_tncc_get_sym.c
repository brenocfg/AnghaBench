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
 void* GetProcAddress (void*,char*) ; 
 void* GetProcAddressA (void*,char*) ; 
 void* dlsym (void*,char*) ; 

__attribute__((used)) static void * tncc_get_sym(void *handle, char *func)
{
	void *fptr;

#ifdef CONFIG_NATIVE_WINDOWS
#ifdef _WIN32_WCE
	fptr = GetProcAddressA(handle, func);
#else /* _WIN32_WCE */
	fptr = GetProcAddress(handle, func);
#endif /* _WIN32_WCE */
#else /* CONFIG_NATIVE_WINDOWS */
	fptr = dlsym(handle, func);
#endif /* CONFIG_NATIVE_WINDOWS */

	return fptr;
}