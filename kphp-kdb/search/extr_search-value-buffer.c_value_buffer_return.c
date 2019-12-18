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
struct value_buffer {char* size_ptr; int w; scalar_t__ n474; scalar_t__ s; scalar_t__ wptr; TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 size_t sprintf (char*,char*,int) ; 

int value_buffer_return (struct value_buffer *B) {
  B->size_ptr[sprintf (B->size_ptr, "% 9d", B->w)] = '\r';
  memcpy (B->wptr, "\r\n", 2);
  B->wptr += 2;
  advance_write_ptr (&B->c->Out, B->wptr - (B->s - B->n474));
  return 0;
}