#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct memblock_t* avail; } ;
typedef  TYPE_1__ svn_spillbuf_t ;
struct memblock_t {struct memblock_t* next; } ;

/* Variables and functions */

__attribute__((used)) static void
return_buffer(svn_spillbuf_t *buf,
              struct memblock_t *mem)
{
  mem->next = buf->avail;
  buf->avail = mem;
}