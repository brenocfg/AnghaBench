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
struct stub {int dummy; } ;

/* Variables and functions */
 char* __progname ; 
 int /*<<< orphan*/  crunched_usage () ; 
 int main (int,char**,char**) ; 
 char* strrchr (char*,char) ; 

int
crunched_main(int argc, char **argv, char **envp)
{
    char *slash;
    struct stub *ep;
    int columns, len;

    if(argc <= 1)
	crunched_usage();

    slash = strrchr(argv[1], '/');
    __progname = slash? slash+1 : argv[1];

    return main(--argc, ++argv, envp);
}