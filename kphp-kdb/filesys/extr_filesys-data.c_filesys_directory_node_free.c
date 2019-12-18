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
struct filesys_directory_node {struct filesys_directory_node* name; } ;

/* Variables and functions */
 int strlen (struct filesys_directory_node*) ; 
 int /*<<< orphan*/  tot_directory_nodes ; 
 int /*<<< orphan*/  zfree (struct filesys_directory_node*,int) ; 

__attribute__((used)) static void filesys_directory_node_free (struct filesys_directory_node *D) {
  tot_directory_nodes--;
  if (D->name != NULL) {
    zfree (D->name, strlen (D->name) + 1);
  }
  zfree (D, sizeof (struct filesys_directory_node));
}