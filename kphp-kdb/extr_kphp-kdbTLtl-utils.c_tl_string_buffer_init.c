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
 int /*<<< orphan*/  memset (struct tl_buffer*,int /*<<< orphan*/ ,int) ; 

void tl_string_buffer_init (struct tl_buffer *b) {
  memset (b, 0, sizeof (*b));
}