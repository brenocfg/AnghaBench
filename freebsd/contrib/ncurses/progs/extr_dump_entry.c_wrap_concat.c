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

/* Variables and functions */
 scalar_t__ INDENT ; 
 scalar_t__ column ; 
 int /*<<< orphan*/  force_wrap () ; 
 int /*<<< orphan*/  outbuf ; 
 char const* separator ; 
 int /*<<< orphan*/  strcpy_DYN (int /*<<< orphan*/ *,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ width ; 

__attribute__((used)) static void
wrap_concat(const char *src)
{
    size_t need = strlen(src);
    size_t want = strlen(separator) + need;

    if (column > INDENT
	&& column + (int) want > width) {
	force_wrap();
    }
    strcpy_DYN(&outbuf, src);
    strcpy_DYN(&outbuf, separator);
    column += (int) need;
}