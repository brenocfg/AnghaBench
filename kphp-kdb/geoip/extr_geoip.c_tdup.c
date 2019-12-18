#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree {int level; int num; scalar_t__ text; int /*<<< orphan*/  mask; TYPE_2__* right; TYPE_1__* left; } ;
struct TYPE_4__ {int num; int level; int extra; int /*<<< orphan*/  mask; scalar_t__ text; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_3__ {int num; int level; int extra; int /*<<< orphan*/  mask; scalar_t__ text; scalar_t__ right; scalar_t__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int total ; 
 int verbosity ; 

void tdup (struct tree* tree) {
  assert (!tree->left);
  assert (!tree->right);
  assert (tree->level < 32);
  if (verbosity >= 3) {
    fprintf (stderr, "%u.%u.%u.%u\n", tree->num >> 24, (tree->num >> 16) & 0xff, (tree->num >> 8) & 0xff, tree->num & 0xff);
  }
  //assert (tree->text == -1);
  tree->left = malloc (sizeof (struct tree));
  tree->left->num = tree->num;
  tree->left->level = tree->level + 1;
  tree->left->left = 0;
  tree->left->right = 0;
  tree->left->extra = 0;
  tree->left->text = tree->text;
  tree->left->extra = (1 << (31 - tree->level));
  tree->left->mask = tree->mask;
  tree->right = malloc (sizeof (struct tree));
  tree->right->num = tree->num + (1 << (31 - tree->level));
  tree->right->level = tree->level + 1;
  tree->right->left = 0;
  tree->right->right = 0;
  tree->right->extra = 0;
  tree->right->text = tree->text;
  tree->right->extra = (1 << (31 - tree->level));
  tree->right->mask = tree->mask;
  tree->text = 0;
  total += 2;
}