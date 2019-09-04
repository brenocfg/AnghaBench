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
struct filesys_directory_node {int mode; int uid; int gid; int modification_time; int inode; int* name; struct filesys_directory_node* next; struct filesys_directory_node* head; struct filesys_directory_node* parent; } ;
typedef  int /*<<< orphan*/  l ;
typedef  int inode_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bread (int*,int) ; 
 int /*<<< orphan*/  tot_directory_nodes ; 
 int /*<<< orphan*/  vkprintf (int,char*,int*) ; 
 int* zmalloc (int) ; 
 struct filesys_directory_node* zmalloc0 (int) ; 

__attribute__((used)) static struct filesys_directory_node *filesys_load_directory_tree (struct filesys_directory_node *parent) {
  inode_id_t inode;
  bread (&inode, sizeof (inode_id_t));
  assert (inode >= -2);
  if (inode == -2LL) {
    return NULL;
  }
  tot_directory_nodes++;
  struct filesys_directory_node *T = zmalloc0 (sizeof (struct filesys_directory_node));
  bread (&T->mode, sizeof (T->mode));
  bread (&T->uid, sizeof (T->uid));
  bread (&T->gid, sizeof (T->gid));
  bread (&T->modification_time, sizeof (T->modification_time));
  int l;
  bread (&l, sizeof (l));
  T->inode = inode;
  T->parent = parent;
  T->name = zmalloc (l + 1);
  T->head = NULL;
  struct filesys_directory_node *tail = NULL;
  bread (T->name, l);
  T->name[l] = 0;

  vkprintf (3, "load_index: %s\n", T->name);

  if (T->inode < 0) {
    struct filesys_directory_node *P;
    while ((P = filesys_load_directory_tree (T)) != NULL ) {
      if (T->head == NULL) {
        T->head = tail = P;
      } else {
        tail->next = P;
        tail = P;
      }
    }
  }
  return T;
}