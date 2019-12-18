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
struct TYPE_2__ {int (* clear ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* prevvidsw ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vesa_clear(video_adapter_t *adp)
{

	return ((*prevvidsw->clear)(adp));
}