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

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int stat (char const*,struct stat*) ; 
 char* strend (char const*) ; 

__attribute__((used)) static int
Stat(const char *fn, struct stat *sb)
{
    int st;

    st = stat(fn, sb);
#ifdef NAMEI_BUG
    if (*fn != 0 && strend(fn)[-1] == '/' && !S_ISDIR(sb->st_mode))
	st = -1;
#endif /* NAMEI_BUG */
    return st;
}