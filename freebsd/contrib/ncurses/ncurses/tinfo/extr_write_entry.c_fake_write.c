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
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static size_t
fake_write(char *dst,
	   unsigned *offset,
	   size_t limit,
	   char *src,
	   size_t want,
	   size_t size)
{
    size_t have = (limit - *offset);

    want *= size;
    if (have > 0) {
	if (want > have)
	    want = have;
	memcpy(dst + *offset, src, want);
	*offset += (unsigned) want;
    } else {
	want = 0;
    }
    return (want / size);
}