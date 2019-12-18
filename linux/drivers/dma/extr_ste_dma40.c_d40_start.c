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
struct d40_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D40_DMA_RUN ; 
 int d40_channel_execute_command (struct d40_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d40_start(struct d40_chan *d40c)
{
	return d40_channel_execute_command(d40c, D40_DMA_RUN);
}