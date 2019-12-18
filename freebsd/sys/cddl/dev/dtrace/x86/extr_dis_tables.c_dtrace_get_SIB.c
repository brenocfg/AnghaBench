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
typedef  int uint_t ;
struct TYPE_3__ {int d86_error; int (* d86_get_byte ) (int /*<<< orphan*/ ) ;int* d86_bytes; int /*<<< orphan*/  d86_len; int /*<<< orphan*/  d86_data; } ;
typedef  TYPE_1__ dis86_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_get_SIB(dis86_t *x, uint_t *ss, uint_t *index, uint_t *base)
{
	int byte;

	if (x->d86_error)
		return;

	byte = x->d86_get_byte(x->d86_data);
	if (byte < 0) {
		x->d86_error = 1;
		return;
	}
	x->d86_bytes[x->d86_len++] = byte;

	*base = byte & 0x7;
	*index = (byte >> 3) & 0x7;
	*ss = (byte >> 6) & 0x3;
}