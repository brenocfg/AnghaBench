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
struct TYPE_3__ {scalar_t__* chunks; } ;
typedef  TYPE_1__ sctp_auth_chklist_t ;

/* Variables and functions */

int
sctp_serialize_auth_chunks(const sctp_auth_chklist_t *list, uint8_t *ptr)
{
	int i, count = 0;

	if (list == NULL)
		return (0);

	for (i = 0; i < 256; i++) {
		if (list->chunks[i] != 0) {
			*ptr++ = i;
			count++;
		}
	}
	return (count);
}