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
struct libalias {int dummy; } ;
struct ip {int dummy; } ;
struct alias_data {int /*<<< orphan*/ * oaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AliasHandleCUSeeMeIn (struct libalias*,struct ip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
protohandlerin(struct libalias *la, struct ip *pip, struct alias_data *ah)
{
	
	AliasHandleCUSeeMeIn(la, pip, *ah->oaddr);
	return (0);
}