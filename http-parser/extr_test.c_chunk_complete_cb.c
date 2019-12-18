#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  http_parser ;
struct TYPE_2__ {scalar_t__ num_chunks; scalar_t__ num_chunks_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* messages ; 
 size_t num_messages ; 
 int /*<<< orphan*/  parser ; 

int
chunk_complete_cb (http_parser *p)
{
  assert(p == &parser);

  /* Here we want to verify that each chunk_header_cb is matched by a
   * chunk_complete_cb, so not only should the total number of calls to
   * both callbacks be the same, but they also should be interleaved
   * properly */
  assert(messages[num_messages].num_chunks ==
         messages[num_messages].num_chunks_complete + 1);

  messages[num_messages].num_chunks_complete++;
  return 0;
}