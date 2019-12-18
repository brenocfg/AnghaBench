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
typedef  unsigned int rlim_t ;
typedef  int /*<<< orphan*/  numbr ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 unsigned int RLIM_INFINITY ; 
 int /*<<< orphan*/  printf (char const*,char const*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void
print_limit(rlim_t limit, unsigned divisor, const char * inf, const char * pfx, const char * sfx, const char * which)
{
    char numbr[64];

    if (limit == RLIM_INFINITY)
	strlcpy(numbr, inf, sizeof(numbr));
    else
	sprintf(numbr, "%jd", (intmax_t)((limit + divisor/2) / divisor));
    printf(pfx, which, numbr);
    printf(sfx, which);

}