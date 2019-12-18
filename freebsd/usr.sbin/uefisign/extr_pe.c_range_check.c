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
struct executable {size_t x_len; } ;
typedef  size_t off_t ;
typedef  size_t intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char const*,size_t,...) ; 

void
range_check(const struct executable *x, off_t off, size_t len,
    const char *name)
{

	if (off < 0) {
		errx(1, "%s starts at negative offset %jd",
		    name, (intmax_t)off);
	}
	if (off >= (off_t)x->x_len) {
		errx(1, "%s starts at %jd, past the end of executable at %zd",
		    name, (intmax_t)off, x->x_len);
	}
	if (len >= x->x_len) {
		errx(1, "%s size %zd is larger than the executable size %zd",
		    name, len, x->x_len);
	}
	if (off + len > x->x_len) {
		errx(1, "%s extends to %jd, past the end of executable at %zd",
		    name, (intmax_t)(off + len), x->x_len);
	}
}