#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_mixer {int /*<<< orphan*/  modify_counter; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  modify_counter; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ mixer_info ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mixer_mixerinfo(struct snd_mixer *m, mixer_info *mi)
{
	bzero((void *)mi, sizeof(*mi));
	strlcpy(mi->id, m->name, sizeof(mi->id));
	strlcpy(mi->name, device_get_desc(m->dev), sizeof(mi->name));
	mi->modify_counter = m->modify_counter;
}