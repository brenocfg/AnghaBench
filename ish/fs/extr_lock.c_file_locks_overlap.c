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
struct file_lock {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static bool file_locks_overlap(struct file_lock *a, struct file_lock *b) {
    return a->end >= b->start && b->end >= a->start;
}