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
struct tl_scheme_object {int type; } ;

/* Variables and functions */
#define  tlso_double 135 
#define  tlso_function 134 
#define  tlso_int 133 
#define  tlso_list 132 
#define  tlso_long 131 
#define  tlso_open_round_bracket 130 
#define  tlso_open_square_bracket 129 
#define  tlso_str 128 

const char *tl_strtype (struct tl_scheme_object *O) {
  switch (O->type) {
    case tlso_int: return "int";
    case tlso_long: return "long";
    case tlso_double: return "double";
    case tlso_str: return "str";
    case tlso_function: return "function";
    case tlso_list: return "list";
    case tlso_open_round_bracket: return "(";
    case tlso_open_square_bracket: return "[";
  }
  return NULL;
}