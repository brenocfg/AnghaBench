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
struct seq_softc {int midi_number; int /*<<< orphan*/ * midis; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
seq_fetch_mid(struct seq_softc *scp, int unit, kobj_t *md)
{

	if (unit >= scp->midi_number || unit < 0)
		return EINVAL;

	*md = scp->midis[unit];

	return 0;
}