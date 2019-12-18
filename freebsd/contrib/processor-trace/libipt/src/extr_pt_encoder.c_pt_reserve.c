#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;
struct pt_encoder {TYPE_1__ config; int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int pte_eos ; 
 int pte_internal ; 

__attribute__((used)) static int pt_reserve(const struct pt_encoder *encoder, unsigned int size)
{
	const uint8_t *begin, *end, *pos;

	if (!encoder)
		return -pte_internal;

	/* The encoder is synchronized at all times. */
	pos = encoder->pos;
	if (!pos)
		return -pte_internal;

	begin = encoder->config.begin;
	end = encoder->config.end;

	pos += size;
	if (pos < begin || end < pos)
		return -pte_eos;

	return 0;
}