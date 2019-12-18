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
struct fw_iso_packet {int dummy; } ;
struct fw_iso_context {int dummy; } ;
struct fw_iso_buffer {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int dummy_queue_iso(struct fw_iso_context *ctx, struct fw_iso_packet *p,
			   struct fw_iso_buffer *buffer, unsigned long payload)
{
	return -ENODEV;
}