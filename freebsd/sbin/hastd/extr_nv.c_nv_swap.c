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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nvhdr {int nvh_type; int nvh_dsize; } ;

/* Variables and functions */
 unsigned char* NVH_DATA (struct nvhdr*) ; 
 int NV_ORDER_HOST ; 
 int NV_ORDER_MASK ; 
 int NV_ORDER_NETWORK ; 
#define  NV_TYPE_INT16 144 
#define  NV_TYPE_INT16_ARRAY 143 
#define  NV_TYPE_INT32 142 
#define  NV_TYPE_INT32_ARRAY 141 
#define  NV_TYPE_INT64 140 
#define  NV_TYPE_INT64_ARRAY 139 
#define  NV_TYPE_INT8 138 
#define  NV_TYPE_INT8_ARRAY 137 
 int NV_TYPE_MASK ; 
#define  NV_TYPE_STRING 136 
#define  NV_TYPE_UINT16 135 
#define  NV_TYPE_UINT16_ARRAY 134 
#define  NV_TYPE_UINT32 133 
#define  NV_TYPE_UINT32_ARRAY 132 
#define  NV_TYPE_UINT64 131 
#define  NV_TYPE_UINT64_ARRAY 130 
#define  NV_TYPE_UINT8 129 
#define  NV_TYPE_UINT8_ARRAY 128 
 int /*<<< orphan*/  PJDLOG_ABORT (char*) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 void* le32toh (int) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv_swap(struct nvhdr *nvh, bool tohost)
{
	unsigned char *data, *end, *p;
	size_t vsize;

	data = NVH_DATA(nvh);
	if (tohost) {
		if ((nvh->nvh_type & NV_ORDER_MASK) == NV_ORDER_HOST)
			return;
		nvh->nvh_dsize = le32toh(nvh->nvh_dsize);
		end = data + nvh->nvh_dsize;
		nvh->nvh_type &= ~NV_ORDER_MASK;
		nvh->nvh_type |= NV_ORDER_HOST;
	} else {
		if ((nvh->nvh_type & NV_ORDER_MASK) == NV_ORDER_NETWORK)
			return;
		end = data + nvh->nvh_dsize;
		nvh->nvh_dsize = htole32(nvh->nvh_dsize);
		nvh->nvh_type &= ~NV_ORDER_MASK;
		nvh->nvh_type |= NV_ORDER_NETWORK;
	}

	vsize = 0;

	switch (nvh->nvh_type & NV_TYPE_MASK) {
	case NV_TYPE_INT8:
	case NV_TYPE_UINT8:
	case NV_TYPE_INT8_ARRAY:
	case NV_TYPE_UINT8_ARRAY:
		break;
	case NV_TYPE_INT16:
	case NV_TYPE_UINT16:
	case NV_TYPE_INT16_ARRAY:
	case NV_TYPE_UINT16_ARRAY:
		if (vsize == 0)
			vsize = 2;
		/* FALLTHROUGH */
	case NV_TYPE_INT32:
	case NV_TYPE_UINT32:
	case NV_TYPE_INT32_ARRAY:
	case NV_TYPE_UINT32_ARRAY:
		if (vsize == 0)
			vsize = 4;
		/* FALLTHROUGH */
	case NV_TYPE_INT64:
	case NV_TYPE_UINT64:
	case NV_TYPE_INT64_ARRAY:
	case NV_TYPE_UINT64_ARRAY:
		if (vsize == 0)
			vsize = 8;
		for (p = data; p < end; p += vsize) {
			if (tohost) {
				switch (vsize) {
				case 2:
					*(uint16_t *)(void *)p =
					    le16toh(*(uint16_t *)(void *)p);
					break;
				case 4:
					*(uint32_t *)(void *)p =
					    le32toh(*(uint32_t *)(void *)p);
					break;
				case 8:
					*(uint64_t *)(void *)p =
					    le64toh(*(uint64_t *)(void *)p);
					break;
				default:
					PJDLOG_ABORT("invalid condition");
				}
			} else {
				switch (vsize) {
				case 2:
					*(uint16_t *)(void *)p =
					    htole16(*(uint16_t *)(void *)p);
					break;
				case 4:
					*(uint32_t *)(void *)p =
					    htole32(*(uint32_t *)(void *)p);
					break;
				case 8:
					*(uint64_t *)(void *)p =
					    htole64(*(uint64_t *)(void *)p);
					break;
				default:
					PJDLOG_ABORT("invalid condition");
				}
			}
		}
		break;
	case NV_TYPE_STRING:
		break;
	default:
		PJDLOG_ABORT("unrecognized type");
	}
}