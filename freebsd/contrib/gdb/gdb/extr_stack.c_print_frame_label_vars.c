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
struct blockvector {int dummy; } ;
struct block {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct block* BLOCKVECTOR_BLOCK (struct blockvector*,int) ; 
 int BLOCKVECTOR_NBLOCKS (struct blockvector*) ; 
 scalar_t__ BLOCK_END (struct block*) ; 
 scalar_t__ BLOCK_FUNCTION (struct block*) ; 
 struct block* BLOCK_SUPERBLOCK (struct block*) ; 
 scalar_t__ alloca (int) ; 
 struct blockvector* blockvector_for_pc (scalar_t__,int*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 struct block* get_frame_block (struct frame_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ print_block_frame_labels (struct block*,int*,struct ui_file*) ; 

__attribute__((used)) static void
print_frame_label_vars (struct frame_info *fi, int this_level_only,
			struct ui_file *stream)
{
  struct blockvector *bl;
  struct block *block = get_frame_block (fi, 0);
  int values_printed = 0;
  int index, have_default = 0;
  char *blocks_printed;
  CORE_ADDR pc = get_frame_pc (fi);

  if (block == 0)
    {
      fprintf_filtered (stream, "No symbol table info available.\n");
      return;
    }

  bl = blockvector_for_pc (BLOCK_END (block) - 4, &index);
  blocks_printed = (char *) alloca (BLOCKVECTOR_NBLOCKS (bl) * sizeof (char));
  memset (blocks_printed, 0, BLOCKVECTOR_NBLOCKS (bl) * sizeof (char));

  while (block != 0)
    {
      CORE_ADDR end = BLOCK_END (block) - 4;
      int last_index;

      if (bl != blockvector_for_pc (end, &index))
	error ("blockvector blotch");
      if (BLOCKVECTOR_BLOCK (bl, index) != block)
	error ("blockvector botch");
      last_index = BLOCKVECTOR_NBLOCKS (bl);
      index += 1;

      /* Don't print out blocks that have gone by.  */
      while (index < last_index
	     && BLOCK_END (BLOCKVECTOR_BLOCK (bl, index)) < pc)
	index++;

      while (index < last_index
	     && BLOCK_END (BLOCKVECTOR_BLOCK (bl, index)) < end)
	{
	  if (blocks_printed[index] == 0)
	    {
	      if (print_block_frame_labels (BLOCKVECTOR_BLOCK (bl, index), &have_default, stream))
		values_printed = 1;
	      blocks_printed[index] = 1;
	    }
	  index++;
	}
      if (have_default)
	return;
      if (values_printed && this_level_only)
	return;

      /* After handling the function's top-level block, stop.
         Don't continue to its superblock, the block of
         per-file symbols.  */
      if (BLOCK_FUNCTION (block))
	break;
      block = BLOCK_SUPERBLOCK (block);
    }

  if (!values_printed && !this_level_only)
    {
      fprintf_filtered (stream, "No catches.\n");
    }
}