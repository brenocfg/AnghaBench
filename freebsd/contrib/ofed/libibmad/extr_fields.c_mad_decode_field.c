#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int bitlen; } ;
typedef  TYPE_1__ ib_field_t ;
typedef  enum MAD_FIELDS { ____Placeholder_MAD_FIELDS } MAD_FIELDS ;

/* Variables and functions */
 int /*<<< orphan*/  _get_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*,void*) ; 
 int /*<<< orphan*/  _get_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  _get_field64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 TYPE_1__* ib_mad_f ; 

void mad_decode_field(uint8_t * buf, enum MAD_FIELDS field, void *val)
{
	const ib_field_t *f = ib_mad_f + field;

	if (!field) {
		*(int *)val = *(int *)buf;
		return;
	}
	if (f->bitlen <= 32) {
		*(uint32_t *) val = _get_field(buf, 0, f);
		return;
	}
	if (f->bitlen == 64) {
		*(uint64_t *) val = _get_field64(buf, 0, f);
		return;
	}
	_get_array(buf, 0, f, val);
}