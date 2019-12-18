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
struct mbnambuf {int nb_last_id; char* nb_buf; scalar_t__ nb_len; } ;

/* Variables and functions */

void
mbnambuf_init(struct mbnambuf *nbp)
{

	nbp->nb_len = 0;
	nbp->nb_last_id = -1;
	nbp->nb_buf[sizeof(nbp->nb_buf) - 1] = '\0';
}