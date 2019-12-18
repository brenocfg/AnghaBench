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
struct packet_writer {int dummy; } ;
struct oid_array {int nr; int /*<<< orphan*/ * oid; } ;
struct object_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ ok_to_give_up (struct object_array const*,struct object_array*) ; 
 int /*<<< orphan*/  packet_writer_write (struct packet_writer*,char*,...) ; 

__attribute__((used)) static int send_acks(struct packet_writer *writer, struct oid_array *acks,
		     const struct object_array *have_obj,
		     struct object_array *want_obj)
{
	int i;

	packet_writer_write(writer, "acknowledgments\n");

	/* Send Acks */
	if (!acks->nr)
		packet_writer_write(writer, "NAK\n");

	for (i = 0; i < acks->nr; i++) {
		packet_writer_write(writer, "ACK %s\n",
				    oid_to_hex(&acks->oid[i]));
	}

	if (ok_to_give_up(have_obj, want_obj)) {
		/* Send Ready */
		packet_writer_write(writer, "ready\n");
		return 1;
	}

	return 0;
}