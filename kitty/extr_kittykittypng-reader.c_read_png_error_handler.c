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
struct custom_error_handler {int /*<<< orphan*/  jb; int /*<<< orphan*/  (* err_handler ) (char*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_const_charp ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 struct custom_error_handler* png_get_error_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_png_error_handler(png_structp png_ptr, png_const_charp msg) {
    struct custom_error_handler *eh;
    eh = png_get_error_ptr(png_ptr);
    if (eh == NULL) fatal("read_png_error_handler: could not retrieve error handler");
    if(eh->err_handler) eh->err_handler("EBADPNG", msg);
    longjmp(eh->jb, 1);
}