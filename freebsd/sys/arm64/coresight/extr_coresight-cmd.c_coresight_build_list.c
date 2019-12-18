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
struct coresight_event {int dummy; } ;
struct coresight_device {int dummy; } ;

/* Variables and functions */
 struct coresight_device* coresight_next_device (struct coresight_device*,struct coresight_event*) ; 

__attribute__((used)) static int
coresight_build_list(struct coresight_device *cs_dev,
    struct coresight_event *event)
{
	struct coresight_device *out;

	out = cs_dev;
	while (out != NULL)
		out = coresight_next_device(out, event);

	return (0);
}