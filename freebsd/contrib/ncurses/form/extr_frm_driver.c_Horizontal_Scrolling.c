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
struct TYPE_4__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ FORM ;

/* Variables and functions */
 int E_REQUEST_DENIED ; 
 scalar_t__ Single_Line_Field (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Horizontal_Scrolling(int (*const fct) (FORM *), FORM *form)
{
  if (Single_Line_Field(form->current))
    return fct(form);
  else
    return (E_REQUEST_DENIED);
}