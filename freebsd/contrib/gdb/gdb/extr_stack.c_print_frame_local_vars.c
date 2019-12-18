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
struct ui_file {int dummy; } ;
struct frame_info {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 scalar_t__ BLOCK_FUNCTION (struct block*) ; 
 struct block* BLOCK_SUPERBLOCK (struct block*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 struct block* get_frame_block (struct frame_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ print_block_frame_locals (struct block*,struct frame_info*,int,struct ui_file*) ; 

__attribute__((used)) static void
print_frame_local_vars (struct frame_info *fi, int num_tabs,
			struct ui_file *stream)
{
  struct block *block = get_frame_block (fi, 0);
  int values_printed = 0;

  if (block == 0)
    {
      fprintf_filtered (stream, "No symbol table info available.\n");
      return;
    }

  while (block != 0)
    {
      if (print_block_frame_locals (block, fi, num_tabs, stream))
	values_printed = 1;
      /* After handling the function's top-level block, stop.
         Don't continue to its superblock, the block of
         per-file symbols.  */
      if (BLOCK_FUNCTION (block))
	break;
      block = BLOCK_SUPERBLOCK (block);
    }

  if (!values_printed)
    {
      fprintf_filtered (stream, "No locals.\n");
    }
}