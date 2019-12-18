#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* filename; struct TYPE_5__* next; } ;
typedef  TYPE_1__ backup_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int strlen (TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

__attribute__((used)) static void backup_file_free (backup_file_t *F) {
  assert (F && F->filename);
  if (F->next) {
    backup_file_free (F->next);
    F->next = 0;
  }
  zfree (F->filename, strlen (F->filename) + 1);
  zfree (F, sizeof (*F));
}