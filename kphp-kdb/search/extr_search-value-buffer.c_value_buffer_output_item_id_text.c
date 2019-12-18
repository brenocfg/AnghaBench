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
struct value_buffer {int dummy; } ;

/* Variables and functions */
 int SHORT_ID (long long) ; 
 int /*<<< orphan*/  value_buffer_output_char_text (struct value_buffer*,char) ; 
 int /*<<< orphan*/  value_buffer_output_int_text (struct value_buffer*,int) ; 

__attribute__((used)) static void value_buffer_output_item_id_text (struct value_buffer *B, long long item_id) {
  int t = SHORT_ID (item_id);
  if (t) {
    value_buffer_output_int_text (B, (int) item_id);
    value_buffer_output_char_text (B, '_');
    value_buffer_output_int_text (B, (int) t);
  } else {
    value_buffer_output_int_text (B, (int) item_id);
  }
}