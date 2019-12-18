#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* hnext; } ;
typedef  TYPE_1__ backup_file_t ;

/* Variables and functions */
 TYPE_1__** B ; 
 int /*<<< orphan*/  backup_file_free (TYPE_1__*) ; 

__attribute__((used)) static void backup_hash_init (void) {
  int i;
  for (i = 0; i < 10007; i++) {
    backup_file_t *F, *W;
    for (F = B[i]; F; F = W) {
      W = F->hnext;
      backup_file_free (F);
    }
    B[i] = 0;
  }
}