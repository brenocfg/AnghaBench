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
struct stack_entry {int tp; scalar_t__ a; } ;
struct TYPE_3__ {scalar_t__ reference_count; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyImage (TYPE_1__*) ; 
#define  ft_image 130 
#define  ft_int 129 
#define  ft_str 128 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

__attribute__((used)) static void free_stack_entry (struct stack_entry *E) {
  switch (E->tp) {
  case ft_int:
  case ft_str:
    break;
  case ft_image:
    vkprintf (4, "free_stack_entry: DestroyImage (image->reference_count: %d)\n", (int) ((Image *) E->a)->reference_count);
    DestroyImage ((Image *) E->a);
  }
}