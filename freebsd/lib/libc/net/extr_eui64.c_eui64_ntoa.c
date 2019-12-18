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
struct eui64 {int* octet; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,int,int,int,int,int,int,int,int) ; 

int
eui64_ntoa(const struct eui64 *id, char *a, size_t len)
{
        int i;

        i = snprintf(a, len, "%02x-%02x-%02x-%02x-%02x-%02x-%02x-%02x",
	    id->octet[0], id->octet[1], id->octet[2], id->octet[3],
	    id->octet[4], id->octet[5], id->octet[6], id->octet[7]);
        if (i < 23 || i >= len)
                return (-1);
        return (0);
}