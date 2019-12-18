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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tuple_callbacks {int dummy; } ;
struct cis_buffer {int len; int* buffer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CISTPL_END ; 
 int ENOSPC ; 

__attribute__((used)) static int
cardbus_build_cis(device_t cbdev, device_t child, int id,
    int len, uint8_t *tupledata, uint32_t start, uint32_t *off,
    struct tuple_callbacks *info, void *argp)
{
	struct cis_buffer *cis;
	int i;

	cis = (struct cis_buffer *)argp;
	/*
	 * CISTPL_END is a special case, it has no length field.
	 */
	if (id == CISTPL_END) {
		if (cis->len + 1 > sizeof(cis->buffer)) {
			cis->len = 0;
			return (ENOSPC);
		}
		cis->buffer[cis->len++] = id;
		return (0);
	}
	if (cis->len + 2 + len > sizeof(cis->buffer)) {
		cis->len = 0;
		return (ENOSPC);
	}
	cis->buffer[cis->len++] = id;
	cis->buffer[cis->len++] = len;
	for (i = 0; i < len; i++)
		cis->buffer[cis->len++] = tupledata[i];
	return (0);
}