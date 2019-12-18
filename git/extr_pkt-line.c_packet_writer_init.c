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
struct packet_writer {int dest_fd; scalar_t__ use_sideband; } ;

/* Variables and functions */

void packet_writer_init(struct packet_writer *writer, int dest_fd)
{
	writer->dest_fd = dest_fd;
	writer->use_sideband = 0;
}