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
struct stack_entry {char* a; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_str ; 
 char* strdup (char*) ; 

__attribute__((used)) static void new_str (struct stack_entry *E, char *str, int clone) {
  E->a = clone ? strdup (str) : str;
  E->tp = ft_str;
}