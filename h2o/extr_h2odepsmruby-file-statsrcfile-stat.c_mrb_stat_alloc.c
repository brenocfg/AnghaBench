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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct stat *
mrb_stat_alloc(mrb_state *mrb)
{
  return (struct stat *)mrb_malloc(mrb, sizeof(struct stat));
}