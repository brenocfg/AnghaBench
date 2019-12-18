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
struct TYPE_6__ {int block_size; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_7__ {int pack_offset; TYPE_1__* fs; } ;
typedef  TYPE_3__ pack_context_t ;
typedef  int apr_off_t ;
struct TYPE_5__ {TYPE_2__* fsap_data; } ;

/* Variables and functions */

__attribute__((used)) static apr_off_t
get_block_left(pack_context_t *context)
{
  svn_fs_x__data_t *ffd = context->fs->fsap_data;
  return ffd->block_size - (context->pack_offset % ffd->block_size);
}