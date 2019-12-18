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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_textbuf_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_textbuf_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ocs_textbuf_copy(ocs_textbuf_t *textbuf, uint8_t *buffer, uint32_t buffer_length)
{
	char *s;

	if (!ocs_textbuf_initialized(textbuf)) {
		return;
	}

	s = (char*) buffer;
	while(*s) {
		ocs_textbuf_putc(textbuf, *s++);
	}

}