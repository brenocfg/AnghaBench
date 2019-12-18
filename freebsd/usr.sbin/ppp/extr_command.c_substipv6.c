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
struct ncpaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ncpaddr_ntoa (struct ncpaddr const*) ; 
 char* subst (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
substipv6(char *tgt, const char *oldstr, const struct ncpaddr *ip)
{
    return subst(tgt, oldstr, ncpaddr_ntoa(ip));
}