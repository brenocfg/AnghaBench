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
typedef  int uint32_t ;
struct TYPE_2__ {int do_pipe; } ;

/* Variables and functions */
 int DN_MAX_ID ; 
 TYPE_1__ co ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static int
parse_range(int ac, char *av[], uint32_t *v, int len)
{
	int n = 0;
	char *endptr, *s;
	uint32_t base[2];

	if (v == NULL || len < 2) {
		v = base;
		len = 2;
	}

	for (s = *av; s != NULL; av++, ac--) {
		v[0] = strtoul(s, &endptr, 10);
		v[1] = (*endptr != '-') ? v[0] :
			 strtoul(endptr+1, &endptr, 10);
		if (*endptr == '\0') { /* prepare for next round */
			s = (ac > 0) ? *(av+1) : NULL;
		} else {
			if (*endptr != ',') {
				warn("invalid number: %s", s);
				s = ++endptr;
				continue;
			}
			/* continue processing from here */
			s = ++endptr;
			ac++;
			av--;
		}
		if (v[1] < v[0] ||
			v[0] >= DN_MAX_ID-1 ||
			v[1] >= DN_MAX_ID-1) {
			continue; /* invalid entry */
		}
		n++;
		/* translate if 'pipe list' */
		if (co.do_pipe == 1) {
			v[0] += DN_MAX_ID;
			v[1] += DN_MAX_ID;
		}
		v = (n*2 < len) ? v + 2 : base;
	}
	return n;
}