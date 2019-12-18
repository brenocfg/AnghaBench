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
struct lev_generic {int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int del_some_groups (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_user (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clear_negative_groups (struct lev_generic *E) {
  return del_some_groups (get_user (E->a), -1);
}