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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  SDP_DATA_SEQ16 130 
#define  SDP_DATA_SEQ32 129 
#define  SDP_DATA_SEQ8 128 
 int /*<<< orphan*/  SDP_GET16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET32 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET8 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_protocol_descriptor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_protocol_descriptor_list(uint8_t const *start, uint8_t const *end)
{
	uint32_t	type, len;

	if (end - start < 2) {
		fprintf(stderr, "Invalid Protocol Descriptor List. " \
				"Too short, len=%zd\n", end - start);
		return;
	}

	SDP_GET8(type, start);
	switch (type) {
	case SDP_DATA_SEQ8:
		SDP_GET8(len, start);
		break;

	case SDP_DATA_SEQ16:
		SDP_GET16(len, start);
		break;

	case SDP_DATA_SEQ32:
		SDP_GET32(len, start);
		break;

	default:
		fprintf(stderr, "Invalid Protocol Descriptor List. " \
				"Not a sequence, type=%#x\n", type);
		return;
		/* NOT REACHED */
	}

	if (len > (end - start)) {
		fprintf(stderr, "Invalid Protocol Descriptor List. " \
				"Too long, len=%d\n", len);
		return;
	}

	while (start < end) {
		SDP_GET8(type, start);
		switch (type) {
		case SDP_DATA_SEQ8:
			SDP_GET8(len, start);
			break;

		case SDP_DATA_SEQ16:
			SDP_GET16(len, start);
			break;

		case SDP_DATA_SEQ32:
			SDP_GET32(len, start);
			break;

		default:
			fprintf(stderr, "Invalid Protocol Descriptor List. " \
					"Not a sequence, type=%#x\n", type);
			return;
			/* NOT REACHED */
		}

		if (len > (end - start)) {
			fprintf(stderr, "Invalid Protocol Descriptor List. " \
					"Too long, len=%d\n", len);
			return;
		}

		print_protocol_descriptor(start, start + len);
		start += len;
	}
}