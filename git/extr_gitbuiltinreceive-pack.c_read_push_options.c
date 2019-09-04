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
struct string_list {int dummy; } ;
struct packet_reader {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ PACKET_READ_NORMAL ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_push_options(struct packet_reader *reader,
			      struct string_list *options)
{
	while (1) {
		if (packet_reader_read(reader) != PACKET_READ_NORMAL)
			break;

		string_list_append(options, reader->line);
	}
}