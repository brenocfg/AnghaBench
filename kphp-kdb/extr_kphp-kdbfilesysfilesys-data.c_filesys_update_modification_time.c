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
struct filesys_directory_node {struct filesys_directory_node* parent; int /*<<< orphan*/  modification_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  now ; 

__attribute__((used)) static void filesys_update_modification_time (struct filesys_directory_node *T) {
  while (T != NULL) {
    T->modification_time = now;
    T = T->parent;
  }
}