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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_2__ {int (* term ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPLASH_TERM ; 
 int /*<<< orphan*/ * splash_adp ; 
 int /*<<< orphan*/  splash_arg ; 
 int splash_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* splash_decoder ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *) ; 

int
splash_term(video_adapter_t *adp)
{
	int error = 0;

	if (splash_adp != adp)
		return EINVAL;
	if (splash_decoder != NULL) {
		if (splash_callback != NULL)
			error = (*splash_callback)(SPLASH_TERM, splash_arg);
		if (error == 0 && splash_decoder->term)
			error = (*splash_decoder->term)(adp);
		if (error == 0)
			splash_decoder = NULL;
	}
	return error;
}