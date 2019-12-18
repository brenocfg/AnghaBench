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
struct stack_entry {int /*<<< orphan*/  tp; int /*<<< orphan*/ * a; } ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 int /*<<< orphan*/  ft_image ; 

__attribute__((used)) static void new_image (struct stack_entry *E, Image *I) {
  E->a =  I;
  E->tp = ft_image;
}