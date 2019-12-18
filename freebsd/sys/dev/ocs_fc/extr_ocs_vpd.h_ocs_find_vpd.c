#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* buffer; scalar_t__ checksum; scalar_t__ offset; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ vpdbuf_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int VPD_LARGE_RESOURCE_TYPE_R_TAG ; 
 int VPD_LARGE_RESOURCE_TYPE_W_TAG ; 
 int VPD_SMALL_RESOURCE_TYPE_END_TAG ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vpddone (TYPE_1__*) ; 
 int vpdnext (TYPE_1__*) ; 
 int* vpdref (TYPE_1__*) ; 

__attribute__((used)) static inline uint8_t *
ocs_find_vpd(uint8_t *vpddata, uint32_t vpddata_length, const char *key)
{
	vpdbuf_t vpdbuf;
	uint8_t *pret = NULL;
	uint8_t c0 = key[0];
	uint8_t c1 = key[1];

	vpdbuf.buffer = (uint8_t*) vpddata;
	vpdbuf.length = vpddata_length;
	vpdbuf.offset = 0;
	vpdbuf.checksum = 0;

	while (!vpddone(&vpdbuf)) {
		int type = vpdnext(&vpdbuf);
		int len_lo;
		int len_hi;
		int len;
		int i;

		if (type == VPD_SMALL_RESOURCE_TYPE_END_TAG) {
			break;
		}

		len_lo = vpdnext(&vpdbuf);
		len_hi = vpdnext(&vpdbuf);
		len = len_lo + (len_hi << 8);

		if ((type == VPD_LARGE_RESOURCE_TYPE_R_TAG) || (type == VPD_LARGE_RESOURCE_TYPE_W_TAG)) {
			while (len > 0) {
				int rc0;
				int rc1;
				int sublen;
				uint8_t *pstart;

				rc0 = vpdnext(&vpdbuf);
				rc1 = vpdnext(&vpdbuf);

				/* Mark this location */
				pstart = vpdref(&vpdbuf);

				sublen = vpdnext(&vpdbuf);

				/* Adjust remaining len */
				len -= (sublen + 3);

				/* check for match with request */
				if ((c0 == rc0) && (c1 == rc1)) {
					pret = pstart;
					for (i = 0; i < sublen; i++) {
						vpdnext(&vpdbuf);
					}
				/* check for "RV" end */
				} else if ('R' == rc0 && 'V' == rc1) {

					/* Read the checksum */
					for (i = 0; i < sublen; i++) {
						vpdnext(&vpdbuf);
					}

					/* The accumulated checksum should be zero here */
					if (vpdbuf.checksum != 0) {
						ocs_log_test(NULL, "checksum error\n");
						return NULL;
					}
				}
				else
					for (i = 0; i < sublen; i++) {
						vpdnext(&vpdbuf);
					}
			}
		}

		for (i = 0; i < len; i++) {
			vpdnext(&vpdbuf);
		}
	}

	return pret;
}