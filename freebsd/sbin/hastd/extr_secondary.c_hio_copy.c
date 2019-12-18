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
struct hio {int /*<<< orphan*/  hio_memsync; int /*<<< orphan*/  hio_length; int /*<<< orphan*/  hio_offset; int /*<<< orphan*/  hio_cmd; int /*<<< orphan*/  hio_seq; } ;

/* Variables and functions */

__attribute__((used)) static void
hio_copy(const struct hio *srchio, struct hio *dsthio)
{

	/*
	 * We don't copy hio_error, hio_data and hio_next fields.
	 */

	dsthio->hio_seq = srchio->hio_seq;
	dsthio->hio_cmd = srchio->hio_cmd;
	dsthio->hio_offset = srchio->hio_offset;
	dsthio->hio_length = srchio->hio_length;
	dsthio->hio_memsync = srchio->hio_memsync;
}