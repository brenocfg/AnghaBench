#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ int128_t ;

/* Variables and functions */
#define  SDP_DATA_SEQ16 133 
#define  SDP_DATA_SEQ32 132 
#define  SDP_DATA_SEQ8 131 
#define  SDP_DATA_UUID128 130 
#define  SDP_DATA_UUID16 129 
#define  SDP_DATA_UUID32 128 
 int /*<<< orphan*/  SDP_GET16 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET32 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET8 (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SDP_GET_UUID128 (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int ntohl (int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 char* sdp_uuid2desc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_service_class_id_list(uint8_t const *start, uint8_t const *end)
{
	uint32_t	type, len, value;

	if (end - start < 2) {
		fprintf(stderr, "Invalid Service Class ID List. " \
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
		fprintf(stderr, "Invalid Service Class ID List. " \
				"Not a sequence, type=%#x\n", type);
		return;
		/* NOT REACHED */
	}

	if (len > (end - start)) {
		fprintf(stderr, "Invalid Service Class ID List. " \
				"Too long len=%d\n", len);
		return;
	}

	while (start < end) {
		SDP_GET8(type, start);
		switch (type) {
		case SDP_DATA_UUID16:
			SDP_GET16(value, start);
			fprintf(stdout, "\t%s (%#4.4x)\n",
					sdp_uuid2desc(value), value);
			break;

		case SDP_DATA_UUID32:
			SDP_GET32(value, start);
			fprintf(stdout, "\t%#8.8x\n", value);
			break;

		case SDP_DATA_UUID128: {
			int128_t	uuid;

			SDP_GET_UUID128(&uuid, start);
			fprintf(stdout, "\t%#8.8x-%4.4x-%4.4x-%4.4x-%4.4x%8.8x\n",
					ntohl(*(uint32_t *)&uuid.b[0]),
					ntohs(*(uint16_t *)&uuid.b[4]),
					ntohs(*(uint16_t *)&uuid.b[6]),
					ntohs(*(uint16_t *)&uuid.b[8]),
					ntohs(*(uint16_t *)&uuid.b[10]),
					ntohl(*(uint32_t *)&uuid.b[12]));
			} break;

		default:
			fprintf(stderr, "Invalid Service Class ID List. " \
					"Not a UUID, type=%#x\n", type);
			return;
			/* NOT REACHED */
		}
	}
}