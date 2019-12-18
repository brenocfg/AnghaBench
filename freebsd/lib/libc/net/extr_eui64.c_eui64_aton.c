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
struct eui64 {unsigned int* octet; } ;

/* Variables and functions */
 int EUI64_LEN ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,...) ; 

int
eui64_aton(const char *a, struct eui64 *e)
{
	int i;
	unsigned int o0, o1, o2, o3, o4, o5, o6, o7;

	/* canonical form */
	i = sscanf(a, "%x-%x-%x-%x-%x-%x-%x-%x",
	    &o0, &o1, &o2, &o3, &o4, &o5, &o6, &o7);
	if (i == EUI64_LEN)
		goto good;
	/* ethernet form */
	i = sscanf(a, "%x:%x:%x:%x:%x:%x:%x:%x",
	    &o0, &o1, &o2, &o3, &o4, &o5, &o6, &o7);
	if (i == EUI64_LEN)
		goto good;
	/* classic fwcontrol/dconschat form */
	i = sscanf(a, "0x%2x%2x%2x%2x%2x%2x%2x%2x",
	    &o0, &o1, &o2, &o3, &o4, &o5, &o6, &o7);
	if (i == EUI64_LEN)
		goto good;
	/* MAC format (-) */
	i = sscanf(a, "%x-%x-%x-%x-%x-%x",
	    &o0, &o1, &o2, &o5, &o6, &o7);
	if (i == 6) {
		o3 = 0xff;
		o4 = 0xfe;
		goto good;
	}
	/* MAC format (:) */
	i = sscanf(a, "%x:%x:%x:%x:%x:%x",
	    &o0, &o1, &o2, &o5, &o6, &o7);
	if (i == 6) {
		o3 = 0xff;
		o4 = 0xfe;
		goto good;
	}

	return (-1);

good:
        e->octet[0]=o0;
	e->octet[1]=o1;
	e->octet[2]=o2;
	e->octet[3]=o3;
	e->octet[4]=o4;
	e->octet[5]=o5;
	e->octet[6]=o6;
	e->octet[7]=o7;

        return (0);
}