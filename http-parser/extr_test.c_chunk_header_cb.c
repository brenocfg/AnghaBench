#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  content_length; } ;
typedef  TYPE_1__ http_parser ;
struct TYPE_6__ {int num_chunks; int /*<<< orphan*/ * chunk_lengths; } ;

/* Variables and functions */
 int MAX_CHUNKS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* messages ; 
 size_t num_messages ; 
 TYPE_1__ parser ; 

int
chunk_header_cb (http_parser *p)
{
  assert(p == &parser);
  int chunk_idx = messages[num_messages].num_chunks;
  messages[num_messages].num_chunks++;
  if (chunk_idx < MAX_CHUNKS) {
    messages[num_messages].chunk_lengths[chunk_idx] = p->content_length;
  }

  return 0;
}