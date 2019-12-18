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
struct athregrec {size_t reg; int val; } ;

/* Variables and functions */
 size_t MAX_MARKERS ; 
 char** markers ; 
 int /*<<< orphan*/  printf (char*,char const*,size_t,int) ; 

__attribute__((used)) static void
op_mark(struct athregrec *a)
{
        const char *s = "UNKNOWN";
        if (a->reg <= MAX_MARKERS)
                s = markers[a->reg];

	printf("mark\t%s (%d): %d\n", s, a->reg, a->val);
}