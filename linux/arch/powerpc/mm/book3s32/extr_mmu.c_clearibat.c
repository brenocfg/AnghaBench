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
struct ppc_bat {scalar_t__ batl; scalar_t__ batu; } ;

/* Variables and functions */
 struct ppc_bat** BATS ; 

__attribute__((used)) static void clearibat(int index)
{
	struct ppc_bat *bat = BATS[index];

	bat[0].batu = 0;
	bat[0].batl = 0;
}