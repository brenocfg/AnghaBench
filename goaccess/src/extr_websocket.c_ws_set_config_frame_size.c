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
struct TYPE_2__ {int max_frm_size; } ;

/* Variables and functions */
 TYPE_1__ wsconfig ; 

void
ws_set_config_frame_size (int max_frm_size)
{
  wsconfig.max_frm_size = max_frm_size;
}