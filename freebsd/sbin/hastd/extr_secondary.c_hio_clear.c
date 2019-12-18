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
struct hio {int hio_memsync; scalar_t__ hio_length; scalar_t__ hio_offset; int /*<<< orphan*/  hio_cmd; scalar_t__ hio_error; scalar_t__ hio_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIO_UNDEF ; 

__attribute__((used)) static void
hio_clear(struct hio *hio)
{

	hio->hio_seq = 0;
	hio->hio_error = 0;
	hio->hio_cmd = HIO_UNDEF;
	hio->hio_offset = 0;
	hio->hio_length = 0;
	hio->hio_memsync = false;
}