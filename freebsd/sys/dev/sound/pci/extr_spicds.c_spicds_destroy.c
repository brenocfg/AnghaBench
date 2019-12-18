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
struct spicds_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SPICDS ; 
 int /*<<< orphan*/  free (struct spicds_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

void
spicds_destroy(struct spicds_info *codec)
{
	snd_mtxfree(codec->lock);
	free(codec, M_SPICDS);
}