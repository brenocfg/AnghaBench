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
 int /*<<< orphan*/  WTAPIOCTLCRT ; 
 int /*<<< orphan*/  dev ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void create(int id)
{
    if(ioctl(dev, WTAPIOCTLCRT, &id) < 0){
	printf("error creating wtap with id=%d\n", id);
    }
}