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
struct tac_handle {int /*<<< orphan*/ * srvr_avs; } ;

/* Variables and functions */
 int MAXAVPAIRS ; 
 int /*<<< orphan*/  init_srvr_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_srvr_avs(struct tac_handle *h)
{
	int i;
	for (i=0; i<MAXAVPAIRS; i++)
		init_srvr_str(&(h->srvr_avs[i]));
}