#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct TYPE_2__ {scalar_t__ la_language; } ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 scalar_t__ language_objc ; 
 struct value* value_of_local (char*,int) ; 

struct value *
value_of_this (int complain)
{
  if (current_language->la_language == language_objc)
    return value_of_local ("self", complain);
  else
    return value_of_local ("this", complain);
}