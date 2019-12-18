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
typedef  int /*<<< orphan*/  uInt ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ decContext ;

/* Variables and functions */

decContext * decContextSetStatusQuiet(decContext *context, uInt status) {
  context->status|=status;
  return context;}