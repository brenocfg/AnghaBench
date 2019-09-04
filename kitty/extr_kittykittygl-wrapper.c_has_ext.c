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
 char* exts ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static int has_ext(const char *ext) {
#ifdef _GLAD_IS_SOME_NEW_VERSION
    if(max_loaded_major < 3) {
#endif
        const char *extensions;
        const char *loc;
        const char *terminator;
        extensions = exts;
        if(extensions == NULL || ext == NULL) {
            return 0;
        }
        while(1) {
            loc = strstr(extensions, ext);
            if(loc == NULL) {
                return 0;
            }
            terminator = loc + strlen(ext);
            if((loc == extensions || *(loc - 1) == ' ') &&
                (*terminator == ' ' || *terminator == '\0')) {
                return 1;
            }
            extensions = terminator;
        }
#ifdef _GLAD_IS_SOME_NEW_VERSION
    } else {
        int index;
        if(exts_i == NULL) return 0;
        for(index = 0; index < num_exts_i; index++) {
            const char *e = exts_i[index];
            if(exts_i[index] != NULL && strcmp(e, ext) == 0) {
                return 1;
            }
        }
    }
#endif
    return 0;
}