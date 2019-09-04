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
struct TYPE_2__ {char* s; } ;
struct tl_scheme_object {scalar_t__ type; TYPE_1__ u; } ;

/* Variables and functions */
 int strlen (char*) ; 
 scalar_t__ tlso_function ; 

int tl_scheme_object_is_colon_terminated_function (struct tl_scheme_object *O) {
  if (O->type != tlso_function) {
    return 0;
  }
  int l = strlen (O->u.s);
  return (l > 0 && O->u.s[l-1] == ':') ? 1 : 0;
}