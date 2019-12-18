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
struct spicds_info {unsigned int format; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

void
spicds_setformat(struct spicds_info *codec, unsigned int format)
{
	snd_mtxlock(codec->lock);
	codec->format = format;
	snd_mtxunlock(codec->lock);
}