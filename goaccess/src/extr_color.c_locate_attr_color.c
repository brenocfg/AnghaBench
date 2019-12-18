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
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;
typedef  TYPE_1__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  A_BLINK ; 
 int /*<<< orphan*/  A_BOLD ; 
 int /*<<< orphan*/  A_NORMAL ; 
 int /*<<< orphan*/  A_REVERSE ; 
 int /*<<< orphan*/  A_UNDERLINE ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static void
locate_attr_color (GColors * color, const char *attr)
{
  if (strstr (attr, "bold"))
    color->attr |= A_BOLD;
  if (strstr (attr, "underline"))
    color->attr |= A_UNDERLINE;
  if (strstr (attr, "normal"))
    color->attr |= A_NORMAL;
  if (strstr (attr, "reverse"))
    color->attr |= A_REVERSE;
  if (strstr (attr, "standout"))
    color->attr |= A_REVERSE;
  if (strstr (attr, "blink"))
    color->attr |= A_BLINK;
}