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
struct value_buffer {int wptr; int w; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,int*,int) ; 

__attribute__((used)) static void value_buffer_output_int_raw (struct value_buffer *B, int t) {
  memcpy (B->wptr, &t, 4);
  B->w += 4;
  B->wptr += 4;
}