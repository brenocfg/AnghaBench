#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ int128_t ;

/* Variables and functions */
#define  SDP_DATA_ALT16 154 
#define  SDP_DATA_ALT32 153 
#define  SDP_DATA_ALT8 152 
#define  SDP_DATA_BOOL 151 
#define  SDP_DATA_INT128 150 
#define  SDP_DATA_INT16 149 
#define  SDP_DATA_INT32 148 
#define  SDP_DATA_INT64 147 
#define  SDP_DATA_INT8 146 
#define  SDP_DATA_NIL 145 
#define  SDP_DATA_SEQ16 144 
#define  SDP_DATA_SEQ32 143 
#define  SDP_DATA_SEQ8 142 
#define  SDP_DATA_STR16 141 
#define  SDP_DATA_STR32 140 
#define  SDP_DATA_STR8 139 
#define  SDP_DATA_UINT128 138 
#define  SDP_DATA_UINT16 137 
#define  SDP_DATA_UINT32 136 
#define  SDP_DATA_UINT64 135 
#define  SDP_DATA_UINT8 134 
#define  SDP_DATA_URL16 133 
#define  SDP_DATA_URL32 132 
#define  SDP_DATA_URL8 131 
#define  SDP_DATA_UUID128 130 
#define  SDP_DATA_UUID16 129 
#define  SDP_DATA_UUID32 128 
 int /*<<< orphan*/  SDP_GET128 (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  SDP_GET16 (int,int const*) ; 
 int /*<<< orphan*/  SDP_GET32 (int,int const*) ; 
 int /*<<< orphan*/  SDP_GET64 (int,int const*) ; 
 int /*<<< orphan*/  SDP_GET8 (int,int const*) ; 
 int /*<<< orphan*/  SDP_GET_UUID128 (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int ntohl (int) ; 
 int ntohs (int) ; 
 char* sdp_uuid2desc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_protocol_descriptor(uint8_t const *start, uint8_t const *end)
{
	union {
		uint8_t		uint8;
		uint16_t	uint16;
		uint32_t	uint32;
		uint64_t	uint64;
		int128_t	int128;
	}			value;
	uint32_t		type, len, param;

	/* Get Protocol UUID */
	SDP_GET8(type, start);
	switch (type) {
	case SDP_DATA_UUID16:
		SDP_GET16(value.uint16, start);
		fprintf(stdout, "\t%s (%#4.4x)\n", sdp_uuid2desc(value.uint16),
				value.uint16);
		break;

	case SDP_DATA_UUID32:
		SDP_GET32(value.uint32, start);
		fprintf(stdout, "\t%#8.8x\n", value.uint32);
		break;

	case SDP_DATA_UUID128:
		SDP_GET_UUID128(&value.int128, start);
		fprintf(stdout, "\t%#8.8x-%4.4x-%4.4x-%4.4x-%4.4x%8.8x\n",
				ntohl(*(uint32_t *)&value.int128.b[0]),
				ntohs(*(uint16_t *)&value.int128.b[4]),
				ntohs(*(uint16_t *)&value.int128.b[6]),
				ntohs(*(uint16_t *)&value.int128.b[8]),
				ntohs(*(uint16_t *)&value.int128.b[10]),
				ntohl(*(uint32_t *)&value.int128.b[12]));
		break;

	default:
		fprintf(stderr, "Invalid Protocol Descriptor. " \
				"Not a UUID, type=%#x\n", type);
		return;
		/* NOT REACHED */
	}

	/* Protocol specific parameters */
	for (param = 1; start < end; param ++) {
		fprintf(stdout, "\t\tProtocol specific parameter #%d: ", param);

		SDP_GET8(type, start);
		switch (type) {
		case SDP_DATA_NIL:
			fprintf(stdout, "nil\n");
			break;

		case SDP_DATA_UINT8:
		case SDP_DATA_INT8:
		case SDP_DATA_BOOL:
			SDP_GET8(value.uint8, start);
			fprintf(stdout, "u/int8/bool %u\n", value.uint8);
			break;

		case SDP_DATA_UINT16:
		case SDP_DATA_INT16:
		case SDP_DATA_UUID16:
			SDP_GET16(value.uint16, start);
			fprintf(stdout, "u/int/uuid16 %u\n", value.uint16);
			break;

		case SDP_DATA_UINT32:
		case SDP_DATA_INT32:
		case SDP_DATA_UUID32:
			SDP_GET32(value.uint32, start);
			fprintf(stdout, "u/int/uuid32 %u\n", value.uint32);
			break;

		case SDP_DATA_UINT64:
		case SDP_DATA_INT64:
			SDP_GET64(value.uint64, start);
			fprintf(stdout, "u/int64 %ju\n", value.uint64);
			break;

		case SDP_DATA_UINT128:
		case SDP_DATA_INT128:
			SDP_GET128(&value.int128, start);
			fprintf(stdout, "u/int128 %#8.8x%8.8x%8.8x%8.8x\n",
				*(uint32_t *)&value.int128.b[0],
				*(uint32_t *)&value.int128.b[4],
				*(uint32_t *)&value.int128.b[8],
				*(uint32_t *)&value.int128.b[12]);
			break;

		case SDP_DATA_UUID128:
			SDP_GET_UUID128(&value.int128, start);
			fprintf(stdout, "uuid128 %#8.8x-%4.4x-%4.4x-%4.4x-%4.4x%8.8x\n",
				ntohl(*(uint32_t *)&value.int128.b[0]),
				ntohs(*(uint16_t *)&value.int128.b[4]),
				ntohs(*(uint16_t *)&value.int128.b[6]),
				ntohs(*(uint16_t *)&value.int128.b[8]),
				ntohs(*(uint16_t *)&value.int128.b[10]),
				ntohl(*(uint32_t *)&value.int128.b[12]));
			break;

		case SDP_DATA_STR8:
		case SDP_DATA_URL8:
			SDP_GET8(len, start);
			for (; start < end && len > 0; start ++, len --)
				fprintf(stdout, "%c", *start);
			fprintf(stdout, "\n");
			break;

		case SDP_DATA_STR16:
		case SDP_DATA_URL16:
			SDP_GET16(len, start);
			for (; start < end && len > 0; start ++, len --)
				fprintf(stdout, "%c", *start);
			fprintf(stdout, "\n");
			break;

		case SDP_DATA_STR32:
		case SDP_DATA_URL32:
			SDP_GET32(len, start);
			for (; start < end && len > 0; start ++, len --)
				fprintf(stdout, "%c", *start);
			fprintf(stdout, "\n");
			break;

		case SDP_DATA_SEQ8:
		case SDP_DATA_ALT8:
			SDP_GET8(len, start);
			for (; start < end && len > 0; start ++, len --)
				fprintf(stdout, "%#2.2x ", *start);
			fprintf(stdout, "\n");
			break;

		case SDP_DATA_SEQ16:
		case SDP_DATA_ALT16:
			SDP_GET16(len, start);
			for (; start < end && len > 0; start ++, len --)
				fprintf(stdout, "%#2.2x ", *start);
			fprintf(stdout, "\n");
			break;

		case SDP_DATA_SEQ32:
		case SDP_DATA_ALT32:
			SDP_GET32(len, start);
			for (; start < end && len > 0; start ++, len --)
				fprintf(stdout, "%#2.2x ", *start);
			fprintf(stdout, "\n");
			break;

		default:
			fprintf(stderr, "Invalid Protocol Descriptor. " \
					"Unknown data type: %#02x\n", type);
			return;
			/* NOT REACHED */
		}
	}
}