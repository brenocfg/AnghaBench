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
struct value_buffer {char* wptr; int /*<<< orphan*/  w; } ;

/* Variables and functions */

__attribute__((used)) static void value_buffer_output_char_text (struct value_buffer *B, char ch ) {
  *(B->wptr) = ch;
  B->w++;
  B->wptr++;
}