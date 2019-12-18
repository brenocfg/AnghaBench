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
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_S16_BE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EINVAL ; 
 scalar_t__ SND_FORMAT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aoa_chan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	DPRINTF(("aoa_chan_setformat: format = %u\n", format));

	if (format != SND_FORMAT(AFMT_S16_BE, 2, 0))
		return (EINVAL);

	return (0);
}