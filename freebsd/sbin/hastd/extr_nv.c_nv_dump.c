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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nvhdr {int nvh_type; char* nvh_name; } ;
struct nv {scalar_t__ nv_error; int /*<<< orphan*/  nv_ebuf; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 unsigned char* NVH_DATA (struct nvhdr*) ; 
 size_t NVH_DSIZE (struct nvhdr*) ; 
 size_t NVH_SIZE (struct nvhdr*) ; 
 int /*<<< orphan*/  NV_CHECK (struct nv*) ; 
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
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 unsigned char* ebuf_data (int /*<<< orphan*/ ,size_t*) ; 
 int errno ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int nv_validate (struct nv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
nv_dump(struct nv *nv)
{
	struct nvhdr *nvh;
	unsigned char *data, *ptr;
	size_t dsize, size;
	unsigned int ii;
	bool swap;

	if (nv_validate(nv, NULL) == -1) {
		printf("error: %d\n", errno);
		return;
	}

	NV_CHECK(nv);
	PJDLOG_ASSERT(nv->nv_error == 0);

	ptr = ebuf_data(nv->nv_ebuf, &size);
	while (size > 0) {
		PJDLOG_ASSERT(size >= sizeof(*nvh) + 2);
		nvh = (struct nvhdr *)ptr;
		PJDLOG_ASSERT(size >= NVH_SIZE(nvh));
		swap = ((nvh->nvh_type & NV_ORDER_MASK) == NV_ORDER_NETWORK);
		dsize = NVH_DSIZE(nvh);
		data = NVH_DATA(nvh);
		printf("  %s", nvh->nvh_name);
		switch (nvh->nvh_type & NV_TYPE_MASK) {
		case NV_TYPE_INT8:
			printf("(int8): %jd", (intmax_t)(*(int8_t *)data));
			break;
		case NV_TYPE_UINT8:
			printf("(uint8): %ju", (uintmax_t)(*(uint8_t *)data));
			break;
		case NV_TYPE_INT16:
			printf("(int16): %jd", swap ?
			    (intmax_t)le16toh(*(int16_t *)(void *)data) :
			    (intmax_t)*(int16_t *)(void *)data);
			break;
		case NV_TYPE_UINT16:
			printf("(uint16): %ju", swap ?
			    (uintmax_t)le16toh(*(uint16_t *)(void *)data) :
			    (uintmax_t)*(uint16_t *)(void *)data);
			break;
		case NV_TYPE_INT32:
			printf("(int32): %jd", swap ?
			    (intmax_t)le32toh(*(int32_t *)(void *)data) :
			    (intmax_t)*(int32_t *)(void *)data);
			break;
		case NV_TYPE_UINT32:
			printf("(uint32): %ju", swap ?
			    (uintmax_t)le32toh(*(uint32_t *)(void *)data) :
			    (uintmax_t)*(uint32_t *)(void *)data);
			break;
		case NV_TYPE_INT64:
			printf("(int64): %jd", swap ?
			    (intmax_t)le64toh(*(int64_t *)(void *)data) :
			    (intmax_t)*(int64_t *)(void *)data);
			break;
		case NV_TYPE_UINT64:
			printf("(uint64): %ju", swap ?
			    (uintmax_t)le64toh(*(uint64_t *)(void *)data) :
			    (uintmax_t)*(uint64_t *)(void *)data);
			break;
		case NV_TYPE_INT8_ARRAY:
			printf("(int8 array):");
			for (ii = 0; ii < dsize; ii++)
				printf(" %jd", (intmax_t)((int8_t *)data)[ii]);
			break;
		case NV_TYPE_UINT8_ARRAY:
			printf("(uint8 array):");
			for (ii = 0; ii < dsize; ii++)
				printf(" %ju", (uintmax_t)((uint8_t *)data)[ii]);
			break;
		case NV_TYPE_INT16_ARRAY:
			printf("(int16 array):");
			for (ii = 0; ii < dsize / 2; ii++) {
				printf(" %jd", swap ?
				    (intmax_t)le16toh(((int16_t *)(void *)data)[ii]) :
				    (intmax_t)((int16_t *)(void *)data)[ii]);
			}
			break;
		case NV_TYPE_UINT16_ARRAY:
			printf("(uint16 array):");
			for (ii = 0; ii < dsize / 2; ii++) {
				printf(" %ju", swap ?
				    (uintmax_t)le16toh(((uint16_t *)(void *)data)[ii]) :
				    (uintmax_t)((uint16_t *)(void *)data)[ii]);
			}
			break;
		case NV_TYPE_INT32_ARRAY:
			printf("(int32 array):");
			for (ii = 0; ii < dsize / 4; ii++) {
				printf(" %jd", swap ?
				    (intmax_t)le32toh(((int32_t *)(void *)data)[ii]) :
				    (intmax_t)((int32_t *)(void *)data)[ii]);
			}
			break;
		case NV_TYPE_UINT32_ARRAY:
			printf("(uint32 array):");
			for (ii = 0; ii < dsize / 4; ii++) {
				printf(" %ju", swap ?
				    (uintmax_t)le32toh(((uint32_t *)(void *)data)[ii]) :
				    (uintmax_t)((uint32_t *)(void *)data)[ii]);
			}
			break;
		case NV_TYPE_INT64_ARRAY:
			printf("(int64 array):");
			for (ii = 0; ii < dsize / 8; ii++) {
				printf(" %ju", swap ?
				    (uintmax_t)le64toh(((uint64_t *)(void *)data)[ii]) :
				    (uintmax_t)((uint64_t *)(void *)data)[ii]);
			}
			break;
		case NV_TYPE_UINT64_ARRAY:
			printf("(uint64 array):");
			for (ii = 0; ii < dsize / 8; ii++) {
				printf(" %ju", swap ?
				    (uintmax_t)le64toh(((uint64_t *)(void *)data)[ii]) :
				    (uintmax_t)((uint64_t *)(void *)data)[ii]);
			}
			break;
		case NV_TYPE_STRING:
			printf("(string): %s", (char *)data);
			break;
		default:
			PJDLOG_ABORT("invalid condition");
		}
		printf("\n");
		ptr += NVH_SIZE(nvh);
		size -= NVH_SIZE(nvh);
	}
}