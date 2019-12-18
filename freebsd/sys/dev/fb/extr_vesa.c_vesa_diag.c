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
struct TYPE_2__ {int (* diag ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 TYPE_1__* prevvidsw ; 
 int stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vesa_adp ; 

__attribute__((used)) static int
vesa_diag(video_adapter_t *adp, int level)
{
	int error;

	/* call the previous handler first */
	error = (*prevvidsw->diag)(adp, level);
	if (error)
		return (error);

	if (adp != vesa_adp)
		return (1);

	if (level <= 0)
		return (0);

	return (0);
}