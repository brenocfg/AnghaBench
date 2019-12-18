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
struct roff {int /*<<< orphan*/  rentab; int /*<<< orphan*/  strtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  roff_setstrn (int /*<<< orphan*/ *,char const*,size_t,char const*,size_t,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
roff_setstr(struct roff *r, const char *name, const char *string,
	int append)
{
	size_t	 namesz;

	namesz = strlen(name);
	roff_setstrn(&r->strtab, name, namesz, string,
	    string ? strlen(string) : 0, append);
	roff_setstrn(&r->rentab, name, namesz, NULL, 0, 0);
}