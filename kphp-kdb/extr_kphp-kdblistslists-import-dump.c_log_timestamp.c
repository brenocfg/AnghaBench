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
struct lev_generic {unsigned int a; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TIMESTAMP ; 
 struct lev_generic* write_alloc (int) ; 

void log_timestamp (unsigned timestamp) {
  struct lev_generic *L = write_alloc (8);
  L->type = LEV_TIMESTAMP;
  L->a = timestamp;
}