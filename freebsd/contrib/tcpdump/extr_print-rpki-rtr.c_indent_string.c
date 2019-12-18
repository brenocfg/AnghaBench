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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */

__attribute__((used)) static char *
indent_string (u_int indent)
{
    static char buf[20];
    u_int idx;

    idx = 0;
    buf[idx] = '\0';

    /*
     * Does the static buffer fit ?
     */
    if (sizeof(buf) < ((indent/8) + (indent %8) + 2)) {
	return buf;
    }

    /*
     * Heading newline.
     */
    buf[idx] = '\n';
    idx++;

    while (indent >= 8) {
	buf[idx] = '\t';
	idx++;
	indent -= 8;
    }

    while (indent > 0) {
	buf[idx] = ' ';
	idx++;
	indent--;
    }

    /*
     * Trailing zero.
     */
    buf[idx] = '\0';

    return buf;
}