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
struct rsvp_common_header {scalar_t__* checksum; } ;

/* Variables and functions */

__attribute__((used)) static void
rsvp_clear_checksum(void *header)
{
    struct rsvp_common_header *rsvp_com_header = (struct rsvp_common_header *) header;

    rsvp_com_header->checksum[0] = 0;
    rsvp_com_header->checksum[1] = 0;
}