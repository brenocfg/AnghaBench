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
typedef  TYPE_1__* my_dest_ptr ;
typedef  TYPE_2__* j_compress_ptr ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_8__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dest; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  jpeg_destroy_compress (TYPE_2__*) ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean
empty_output_buffer (j_compress_ptr cinfo)
{
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
  
  jpeg_destroy_compress(cinfo);
  
  // Make crash fatal or we would probably leak memory.
  ri.Error(ERR_FATAL, "Output buffer for encoded JPEG image has insufficient size of %d bytes",
           dest->size);

  return FALSE;
}