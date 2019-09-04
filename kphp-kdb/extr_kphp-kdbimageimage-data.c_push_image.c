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
struct forth_stack {size_t top; int /*<<< orphan*/ * x; } ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 int /*<<< orphan*/  new_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_image (struct forth_stack *st, Image *image) {
  st->top++;
  new_image (&st->x[st->top], image);
}