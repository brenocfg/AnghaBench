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
struct shminfo {int /*<<< orphan*/  shmall; int /*<<< orphan*/  shmseg; int /*<<< orphan*/  shmmni; int /*<<< orphan*/  shmmin; int /*<<< orphan*/  shmmax; } ;
struct l_shminfo64 {int /*<<< orphan*/  shmall; int /*<<< orphan*/  shmseg; int /*<<< orphan*/  shmmni; int /*<<< orphan*/  shmmin; int /*<<< orphan*/  shmmax; } ;

/* Variables and functions */

__attribute__((used)) static void
bsd_to_linux_shminfo( struct shminfo *bpp, struct l_shminfo64 *lpp)
{

	lpp->shmmax = bpp->shmmax;
	lpp->shmmin = bpp->shmmin;
	lpp->shmmni = bpp->shmmni;
	lpp->shmseg = bpp->shmseg;
	lpp->shmall = bpp->shmall;
}