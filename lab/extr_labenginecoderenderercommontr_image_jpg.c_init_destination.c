#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* my_dest_ptr ;
typedef  TYPE_3__* j_compress_ptr ;
struct TYPE_7__ {int /*<<< orphan*/  dest; } ;
struct TYPE_5__ {int /*<<< orphan*/  free_in_buffer; int /*<<< orphan*/  next_output_byte; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; TYPE_1__ pub; int /*<<< orphan*/  outfile; } ;

/* Variables and functions */

__attribute__((used)) static void
init_destination (j_compress_ptr cinfo)
{
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

  dest->pub.next_output_byte = dest->outfile;
  dest->pub.free_in_buffer = dest->size;
}