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
struct protoent_data {int stayopen; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_PROTOCOLS ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

void
__setprotoent_p(int f, struct protoent_data *ped)
{
	if (ped->fp == NULL)
		ped->fp = fopen(_PATH_PROTOCOLS, "re");
	else
		rewind(ped->fp);
	ped->stayopen |= f;
}