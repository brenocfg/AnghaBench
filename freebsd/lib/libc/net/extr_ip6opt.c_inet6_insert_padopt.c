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
typedef  int u_char ;

/* Variables and functions */
 int IP6OPT_PAD1 ; 
 int IP6OPT_PADN ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
inet6_insert_padopt(u_char *p, int len)
{
	switch(len) {
	 case 0:
		 return;
	 case 1:
		 p[0] = IP6OPT_PAD1;
		 return;
	 default:
		 p[0] = IP6OPT_PADN;
		 p[1] = len - 2; 
		 memset(&p[2], 0, len - 2);
		 return;
	}
}