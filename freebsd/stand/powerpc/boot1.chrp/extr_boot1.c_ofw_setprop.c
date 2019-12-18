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
typedef  int u_ofwh_t ;
typedef  int ofwh_t ;
typedef  int ofwcell_t ;

/* Variables and functions */
 scalar_t__ ofw (int*) ; 
 int /*<<< orphan*/  printf (char*,int,void*,size_t) ; 
 scalar_t__ stub1 (int*) ; 

__attribute__((used)) static int
ofw_setprop(ofwh_t ofwh, const char *name, void *buf, size_t len)
{
	ofwcell_t args[] = {
		(ofwcell_t)"setprop",
		4,
		1,
		(u_ofwh_t)ofwh,
		(ofwcell_t)name,
		(ofwcell_t)buf,
		len,
	0
	};

	if ((*ofw)(args)) {
		printf("ofw_setprop: ofwh=0x%x buf=%p len=%u\n",
			ofwh, buf, len);
		return (1);
	}
	return (0);
}