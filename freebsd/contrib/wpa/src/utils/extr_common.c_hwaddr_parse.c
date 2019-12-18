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
typedef  int u8 ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int hex2byte (char const*) ; 

__attribute__((used)) static const char * hwaddr_parse(const char *txt, u8 *addr)
{
	size_t i;

	for (i = 0; i < ETH_ALEN; i++) {
		int a;

		a = hex2byte(txt);
		if (a < 0)
			return NULL;
		txt += 2;
		addr[i] = a;
		if (i < ETH_ALEN - 1 && *txt++ != ':')
			return NULL;
	}
	return txt;
}