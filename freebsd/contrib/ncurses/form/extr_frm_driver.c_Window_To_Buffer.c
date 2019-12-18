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
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FORM ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  _nc_get_fieldbuffer (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Window_To_Buffer(FORM *form, FIELD *field)
{
  _nc_get_fieldbuffer(form, field, field->buf);
}