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
struct units {char const* name; int mult; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,char const*) ; 
 int stub1 (int,unsigned int) ; 
 int stub2 (char*,size_t,int,char const*,int) ; 

__attribute__((used)) static int
unparse_something (int num, const struct units *units, char *s, size_t len,
		   int (*print) (char *, size_t, int, const char *, int),
		   int (*update) (int, unsigned),
		   const char *zero_string)
{
    const struct units *u;
    int ret = 0, tmp;

    if (num == 0)
	return snprintf (s, len, "%s", zero_string);

    for (u = units; num > 0 && u->name; ++u) {
	int divisor;

	divisor = num / u->mult;
	if (divisor) {
	    num = (*update) (num, u->mult);
	    tmp = (*print) (s, len, divisor, u->name, num);
	    if (tmp < 0)
		return tmp;
	    if (tmp > (int) len) {
		len = 0;
		s = NULL;
	    } else {
		len -= tmp;
		s += tmp;
	    }
	    ret += tmp;
	}
    }
    return ret;
}