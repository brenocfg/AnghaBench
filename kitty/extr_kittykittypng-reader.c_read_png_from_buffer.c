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
struct fake_file {scalar_t__ cur; scalar_t__ buf; scalar_t__ sz; } ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  int /*<<< orphan*/  png_bytep ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 struct fake_file* png_get_io_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_png_from_buffer(png_structp png, png_bytep out, png_size_t length) {
    struct fake_file *f = png_get_io_ptr(png);
    if (f) {
        size_t amt = MIN(length, f->sz - f->cur);
        memcpy(out, f->buf + f->cur, amt);
        f->cur += amt;
    }
}