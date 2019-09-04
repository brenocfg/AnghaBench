#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* my_src_ptr ;
typedef  TYPE_2__* j_decompress_ptr ;
struct TYPE_5__ {int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  start_of_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void my_init_source( j_decompress_ptr cinfo ){
	my_src_ptr src = (my_src_ptr) cinfo->src;

	/* We reset the empty-input-file flag for each image,
	 * but we don't clear the input buffer.
	 * This is correct behavior for reading a series of images from one source.
	 */
	src->start_of_file = TRUE;
}