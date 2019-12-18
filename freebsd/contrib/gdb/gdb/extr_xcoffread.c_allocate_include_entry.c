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
typedef  int /*<<< orphan*/  InclTable ;

/* Variables and functions */
 int INITIAL_INCLUDE_TABLE_LENGTH ; 
 int inclIndx ; 
 int inclLength ; 
 int /*<<< orphan*/ * inclTable ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
allocate_include_entry (void)
{
  if (inclTable == NULL)
    {
      inclTable = (InclTable *)
	xmalloc (sizeof (InclTable) * INITIAL_INCLUDE_TABLE_LENGTH);
      memset (inclTable,
	      '\0', sizeof (InclTable) * INITIAL_INCLUDE_TABLE_LENGTH);
      inclLength = INITIAL_INCLUDE_TABLE_LENGTH;
      inclIndx = 0;
    }
  else if (inclIndx >= inclLength)
    {
      inclLength += INITIAL_INCLUDE_TABLE_LENGTH;
      inclTable = (InclTable *)
	xrealloc (inclTable, sizeof (InclTable) * inclLength);
      memset (inclTable + inclLength - INITIAL_INCLUDE_TABLE_LENGTH,
	      '\0', sizeof (InclTable) * INITIAL_INCLUDE_TABLE_LENGTH);
    }
}