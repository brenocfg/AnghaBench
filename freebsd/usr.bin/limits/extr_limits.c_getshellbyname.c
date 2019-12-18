#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int SH_SH ; 
 TYPE_1__* shellparm ; 
 int strcspn (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
getshellbyname(const char * shell)
{
    int i;
    const char * q;
    const char * p = strrchr(shell, '/');

    p = p ? p+1 : shell;
    for (i = 0; (q = shellparm[i].name) != NULL; i++) {
	while (*q) {
	    int j = strcspn(q, "|");

	    if (j == 0)
		break;
	    if (strncmp(p, q, j) == 0)
		return i;
	    if (*(q += j))
		++q;
	}
    }
    return SH_SH;
}