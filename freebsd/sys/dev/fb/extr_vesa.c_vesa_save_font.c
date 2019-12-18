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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int (* save_font ) (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int) ;} ;

/* Variables and functions */
 TYPE_1__* prevvidsw ; 
 int stub1 (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
vesa_save_font(video_adapter_t *adp, int page, int fontsize, int fontwidth,
	       u_char *data, int ch, int count)
{

	return ((*prevvidsw->save_font)(adp, page, fontsize, fontwidth, data,
	    ch, count));
}