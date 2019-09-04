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
 int /*<<< orphan*/  free (char*) ; 
 char* realpath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static inline bool
safe_realpath(const char* src, char *buf, size_t buf_sz) {
    char* ans = realpath(src, NULL);
    if (ans == NULL) return false;
    snprintf(buf, buf_sz, "%s", ans);
    free(ans);
    return true;
}