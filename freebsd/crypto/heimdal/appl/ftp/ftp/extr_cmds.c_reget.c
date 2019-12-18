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
 scalar_t__ TYPE_I ; 
 scalar_t__ curtype ; 
 int /*<<< orphan*/  getit (int,char**,int,char*) ; 

void
reget(int argc, char **argv)
{
    getit(argc, argv, 1, curtype == TYPE_I ? "r+wb" : "r+w");
}