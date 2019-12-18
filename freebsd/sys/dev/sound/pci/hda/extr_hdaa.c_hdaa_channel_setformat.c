#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__* fmtlist; } ;
struct hdaa_chan {scalar_t__ fmt; TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
hdaa_channel_setformat(kobj_t obj, void *data, uint32_t format)
{
	struct hdaa_chan *ch = data;
	int i;

	for (i = 0; ch->caps.fmtlist[i] != 0; i++) {
		if (format == ch->caps.fmtlist[i]) {
			ch->fmt = format;
			return (0);
		}
	}

	return (EINVAL);
}