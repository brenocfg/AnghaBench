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
struct value_buffer {int w; int wptr; } ;

/* Variables and functions */
 int sprintf (int,char*,long long) ; 

__attribute__((used)) static void value_buffer_output_hex_long_text (struct value_buffer *B, long long t) {
  int o;
  B->w += o = sprintf (B->wptr, "%llx", t);
  B->wptr += o;
}