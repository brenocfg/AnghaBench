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
struct packet_writer {int /*<<< orphan*/  dest_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  packet_flush (int /*<<< orphan*/ ) ; 

void packet_writer_flush(struct packet_writer *writer)
{
	packet_flush(writer->dest_fd);
}