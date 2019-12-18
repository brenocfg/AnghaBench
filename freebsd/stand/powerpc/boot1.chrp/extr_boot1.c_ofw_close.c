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
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ stub1 (int*) ; 

__attribute__((used)) static int
ofw_close(ofwh_t devh)
{
	ofwcell_t args[] = {
		(ofwcell_t)"close",
		1,
		0,
		(u_ofwh_t)devh
	};

	if ((*ofw)(args)) {
		printf("ofw_close: devh=0x%x\n", devh);
		return (1);
	}
	return (0);
}