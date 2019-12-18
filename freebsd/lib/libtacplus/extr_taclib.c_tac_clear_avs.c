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
struct tac_handle {int /*<<< orphan*/ * avs; } ;

/* Variables and functions */
 int MAXAVPAIRS ; 
 int /*<<< orphan*/  save_str (struct tac_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
tac_clear_avs(struct tac_handle *h)
{
	int i;
	for (i=0; i<MAXAVPAIRS; i++)
		save_str(h, &(h->avs[i]), NULL, 0);
}