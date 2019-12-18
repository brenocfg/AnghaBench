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
struct tl_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_string_buffer_append_char (struct tl_buffer*,char) ; 

__attribute__((used)) static void indent (struct tl_buffer *b, int depth) {
  while (--depth >= 0) {
    tl_string_buffer_append_char (b, '\t');
  }
}