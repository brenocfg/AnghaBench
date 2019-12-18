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

/* Variables and functions */
 int* a ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 int xx1 ; 
 int xx2 ; 
 int* xxa ; 
 int xxyy () ; 

int main(int argc, char** argv)
{
	printf("xx1=%d, xx2=%d, xxa[5]=%d, a[5]=%d, xxyy()=%d\n",
	    xx1, xx2, xxa[5], a[5], xxyy());
}