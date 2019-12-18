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
struct TYPE_3__ {void* va_token; } ;
typedef  TYPE_1__ video_adapter_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

int
vid_release(video_adapter_t *adp, void *id)
{
	int error;
	int s;

	s = spltty();
	if (adp->va_token == NULL) {
		error = EINVAL;
	} else if (adp->va_token != id) {
		error = EPERM;
	} else {
		adp->va_token = NULL;
		error = 0;
	}
	splx(s);
	return error;
}