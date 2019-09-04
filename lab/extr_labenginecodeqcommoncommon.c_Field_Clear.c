#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ scroll; scalar_t__ cursor; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ field_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_EDIT_LINE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Field_Clear( field_t *edit ) {
  memset(edit->buffer, 0, MAX_EDIT_LINE);
	edit->cursor = 0;
	edit->scroll = 0;
}