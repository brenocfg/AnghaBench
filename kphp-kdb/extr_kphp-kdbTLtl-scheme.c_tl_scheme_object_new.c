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
typedef  enum tl_scheme_object_type { ____Placeholder_tl_scheme_object_type } tl_scheme_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct tl_scheme_object obj_empty_list ; 
 int tlso_list ; 
 int tlso_open_round_bracket ; 
 int tlso_open_square_bracket ; 
 struct tl_scheme_object* zmalloc0 (int) ; 

struct tl_scheme_object *tl_scheme_object_new (enum tl_scheme_object_type type) {
  if (type == tlso_list) {
    return &obj_empty_list;
  }
  assert (type != tlso_open_square_bracket && type != tlso_open_round_bracket);
  struct tl_scheme_object *O = zmalloc0 (sizeof (struct tl_scheme_object));
  O->type = type;
  return O;
}