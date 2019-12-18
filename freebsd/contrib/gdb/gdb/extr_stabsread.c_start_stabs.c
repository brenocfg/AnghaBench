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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * common_block_name ; 
 int /*<<< orphan*/ * global_stabs ; 
 int n_this_object_header_files ; 
 struct type** type_vector ; 
 scalar_t__ type_vector_length ; 

void
start_stabs (void)
{
  global_stabs = NULL;		/* AIX COFF */
  /* Leave FILENUM of 0 free for builtin types and this file's types.  */
  n_this_object_header_files = 1;
  type_vector_length = 0;
  type_vector = (struct type **) 0;

  /* FIXME: If common_block_name is not already NULL, we should complain().  */
  common_block_name = NULL;
}