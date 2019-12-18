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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int /*<<< orphan*/  st_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 int stat (char const*,struct stat*) ; 
 long long strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static time_t
get_tstamp(const char *b)
{
    struct stat st;
    char *eb;
    long long l;

    if (stat(b, &st) != -1)
        return (time_t)st.st_mtime;

    errno = 0;
    l = strtoll(b, &eb, 0);
    if (b == eb || *eb || errno)
        errx(EXIT_FAILURE, "Can't parse timestamp '%s'", b);
    return (time_t)l;
}