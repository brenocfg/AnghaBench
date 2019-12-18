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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; int /*<<< orphan*/  sun_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,char,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
prepare_ifsun(struct sockaddr_un *ifsun, const char *path)
{

    memset(ifsun, '\0', sizeof(*ifsun));
#if !defined(__linux__) && !defined(__solaris__)
    ifsun->sun_len = strlen(path);
#endif
    ifsun->sun_family = AF_LOCAL;
    strcpy(ifsun->sun_path, path);
}