#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* my_src_ptr ;
typedef  TYPE_3__* j_decompress_ptr ;
struct TYPE_8__ {int /*<<< orphan*/  src; } ;
struct TYPE_6__ {size_t next_input_byte; scalar_t__ bytes_in_buffer; } ;
struct TYPE_7__ {TYPE_1__ pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  my_fill_input_buffer (TYPE_3__*) ; 

__attribute__((used)) static void my_skip_input_data( j_decompress_ptr cinfo, long num_bytes ){
	my_src_ptr src = (my_src_ptr) cinfo->src;

	/* Just a dumb implementation for now.  Could use fseek() except
	 * it doesn't work on pipes.  Not clear that being smart is worth
	 * any trouble anyway --- large skips are infrequent.
	 */
	if ( num_bytes > 0 ) {
		while ( num_bytes > (long) src->pub.bytes_in_buffer ) {
			num_bytes -= (long) src->pub.bytes_in_buffer;
			(void) my_fill_input_buffer( cinfo );
			/* note we assume that fill_input_buffer will never return FALSE,
			 * so suspension need not be handled.
			 */
		}
		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}