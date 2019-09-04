#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct jpeg_source_mgr {int dummy; } ;
typedef  TYPE_3__* my_src_ptr ;
typedef  int /*<<< orphan*/  my_source_mgr ;
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_9__ {struct jpeg_source_mgr* src; TYPE_1__* mem; } ;
struct TYPE_7__ {int /*<<< orphan*/ * next_input_byte; scalar_t__ bytes_in_buffer; int /*<<< orphan*/  term_source; int /*<<< orphan*/  resync_to_restart; int /*<<< orphan*/  skip_input_data; int /*<<< orphan*/  fill_input_buffer; int /*<<< orphan*/  init_source; } ;
struct TYPE_8__ {int src_size; TYPE_2__ pub; int /*<<< orphan*/ * src_buffer; int /*<<< orphan*/ * buffer; } ;
struct TYPE_6__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  JOCTET ;

/* Variables and functions */
 int INPUT_BUF_SIZE ; 
 int /*<<< orphan*/  JPOOL_PERMANENT ; 
 int /*<<< orphan*/  jpeg_resync_to_restart ; 
 int /*<<< orphan*/  my_fill_input_buffer ; 
 int /*<<< orphan*/  my_init_source ; 
 int /*<<< orphan*/  my_skip_input_data ; 
 int /*<<< orphan*/  my_term_source ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void jpeg_buffer_src( j_decompress_ptr cinfo, void* buffer, int bufsize ){
	my_src_ptr src;

	/* The source object and input buffer are made permanent so that a series
	 * of JPEG images can be read from the same file by calling jpeg_stdio_src
	 * only before the first one.  (If we discarded the buffer at the end of
	 * one image, we'd likely lose the start of the next one.)
	 * This makes it unsafe to use this manager and a different source
	 * manager serially with the same JPEG object.  Caveat programmer.
	 */
	if ( cinfo->src == NULL ) { /* first time for this JPEG object? */
		cinfo->src = (struct jpeg_source_mgr *)
					 ( *cinfo->mem->alloc_small )( (j_common_ptr) cinfo, JPOOL_PERMANENT,
												   sizeof( my_source_mgr ) );
		src = (my_src_ptr) cinfo->src;
		src->buffer = (JOCTET *)
					  ( *cinfo->mem->alloc_small )( (j_common_ptr) cinfo, JPOOL_PERMANENT,
													INPUT_BUF_SIZE * sizeof( JOCTET ) );
	}

	src = (my_src_ptr) cinfo->src;
	src->pub.init_source = my_init_source;
	src->pub.fill_input_buffer = my_fill_input_buffer;
	src->pub.skip_input_data = my_skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
	src->pub.term_source = my_term_source;
	src->src_buffer = (JOCTET *)buffer;
	src->src_size = bufsize;
	src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
	src->pub.next_input_byte = NULL; /* until buffer loaded */
}