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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int MAX_LENGTH_CANON ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static size_t
parse_vector(char *buf, uint32_t *v)
{
    char *last;
    unsigned ret = 0;
    const char *n;
    unsigned u;

    for(n = strtok_r(buf, " ", &last);
	n != NULL;
	n = strtok_r(NULL, " ", &last)) {
	if (ret >= MAX_LENGTH_CANON) {
	    errx(1, "increase MAX_LENGTH_CANON");
	}
	if (sscanf(n, "%x", &u) != 1) {
	    errx(1, "failed to parse hex: %s", n);
	}
	v[ret] = u;
	++ret;
    }
    return ret;
}