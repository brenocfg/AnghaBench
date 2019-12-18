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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct mtx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (struct mtx*) ; 

void
snd_mtxfree(void *m)
{
	struct mtx *mtx = m;

	mtx_destroy(mtx);
	free(mtx, M_DEVBUF);
}