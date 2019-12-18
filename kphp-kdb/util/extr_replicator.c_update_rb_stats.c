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
struct related_binlog {scalar_t__ status; } ;

/* Variables and functions */
 int classify_slave (struct related_binlog*) ; 
 int /*<<< orphan*/  update_rb_stats_copy (struct related_binlog*,scalar_t__,int) ; 

__attribute__((used)) static void update_rb_stats (struct related_binlog *R) {
  if (R->status) {
    int st = classify_slave (R);
    update_rb_stats_copy (R, R->status, st);
    update_rb_stats_copy (R, R->status + 1, st);
  }
}