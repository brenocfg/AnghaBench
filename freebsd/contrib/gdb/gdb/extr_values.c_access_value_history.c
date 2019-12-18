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
struct value_history_chunk {int /*<<< orphan*/ * values; struct value_history_chunk* next; } ;
struct value {int dummy; } ;

/* Variables and functions */
 int VALUE_HISTORY_CHUNK ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct value* value_copy (int /*<<< orphan*/ ) ; 
 struct value_history_chunk* value_history_chain ; 
 int value_history_count ; 

struct value *
access_value_history (int num)
{
  struct value_history_chunk *chunk;
  int i;
  int absnum = num;

  if (absnum <= 0)
    absnum += value_history_count;

  if (absnum <= 0)
    {
      if (num == 0)
	error ("The history is empty.");
      else if (num == 1)
	error ("There is only one value in the history.");
      else
	error ("History does not go back to $$%d.", -num);
    }
  if (absnum > value_history_count)
    error ("History has not yet reached $%d.", absnum);

  absnum--;

  /* Now absnum is always absolute and origin zero.  */

  chunk = value_history_chain;
  for (i = (value_history_count - 1) / VALUE_HISTORY_CHUNK - absnum / VALUE_HISTORY_CHUNK;
       i > 0; i--)
    chunk = chunk->next;

  return value_copy (chunk->values[absnum % VALUE_HISTORY_CHUNK]);
}