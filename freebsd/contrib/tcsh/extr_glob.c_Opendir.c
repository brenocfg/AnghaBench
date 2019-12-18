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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static DIR *
Opendir(const char *str)
{
#if defined(hpux) || defined(__hpux)
    struct stat st;
#endif

    if (!*str)
	return (opendir("."));
#if defined(hpux) || defined(__hpux)
    /*
     * Opendir on some device files hangs, so avoid it
     */
    if (stat(str, &st) == -1 || !S_ISDIR(st.st_mode))
	return NULL;
#endif
    return opendir(str);
}