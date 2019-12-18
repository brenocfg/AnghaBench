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
struct ac97_info {int /*<<< orphan*/  lock; int /*<<< orphan*/ * methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AC97 ; 
 int /*<<< orphan*/  free (struct ac97_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 

void
ac97_destroy(struct ac97_info *codec)
{
	snd_mtxlock(codec->lock);
	if (codec->methods != NULL)
		kobj_delete(codec->methods, M_AC97);
	snd_mtxfree(codec->lock);
	free(codec, M_AC97);
}