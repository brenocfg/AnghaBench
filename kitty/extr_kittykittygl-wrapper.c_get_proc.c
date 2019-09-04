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
 void* dlsym (int /*<<< orphan*/ *,char const*) ; 
 void* gladGetProcAddressPtr (char const*) ; 
 int /*<<< orphan*/ * libGL ; 

__attribute__((used)) static
void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;
#if !defined(__APPLE__) && !defined(__HAIKU__)
    if(gladGetProcAddressPtr != NULL) {
        result = gladGetProcAddressPtr(namez);
    }
#endif
    if(result == NULL) {
#if defined(_WIN32) || defined(__CYGWIN__)
        result = (void*)GetProcAddress((HMODULE) libGL, namez);
#else
        result = dlsym(libGL, namez);
#endif
    }
    return result;
}