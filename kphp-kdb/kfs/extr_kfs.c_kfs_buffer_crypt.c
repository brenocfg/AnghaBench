#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* kfs_file_handle_t ;
struct TYPE_5__ {TYPE_1__* info; } ;
struct TYPE_4__ {scalar_t__ iv; int /*<<< orphan*/  replica; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_crypt (int /*<<< orphan*/ ,unsigned char*,long long,scalar_t__,long long) ; 

void kfs_buffer_crypt (kfs_file_handle_t F, void *buff, long long size, long long off) {
  assert (off >= 0);
  if (F && F->info && F->info->iv) {
    buffer_crypt (F->info->replica, (unsigned char *) buff, size, F->info->iv, off);
  }
}