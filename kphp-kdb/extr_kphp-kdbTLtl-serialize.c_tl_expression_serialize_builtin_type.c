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
struct tl_scheme_object {int dummy; } ;
struct tl_int_array {int dummy; } ;
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 int CODE_double ; 
 int CODE_int ; 
 int CODE_long ; 
 int CODE_string ; 
 int /*<<< orphan*/  isupper (char const) ; 
 int /*<<< orphan*/  strcmp (char const* const,char*) ; 
 int /*<<< orphan*/  tl_int_array_append (struct tl_int_array*,int) ; 
 int /*<<< orphan*/  tl_int_array_append_double (struct tl_int_array*,double) ; 
 int /*<<< orphan*/  tl_int_array_append_long (struct tl_int_array*,long long) ; 
 int /*<<< orphan*/  tl_int_array_append_string (struct tl_int_array*,char*) ; 
 int /*<<< orphan*/  tl_scheme_double_value (struct tl_scheme_object*,double*) ; 
 int /*<<< orphan*/  tl_scheme_int_value (struct tl_scheme_object*,int*) ; 
 int /*<<< orphan*/  tl_scheme_long_value (struct tl_scheme_object*,long long*) ; 
 int /*<<< orphan*/  tl_scheme_string_value (struct tl_scheme_object*,char**) ; 
 int tl_serialize_failf (struct tl_compiler*,struct tl_scheme_object*,char*) ; 
 int tolower (char const) ; 

int tl_expression_serialize_builtin_type (struct tl_compiler *C, struct tl_scheme_object *E, const char *const name, struct tl_int_array *a) {
  int i;
  long long l;
  double d;
  char *s;
  switch (tolower (name[0])) {
    case 'd':
      if (!strcmp (name + 1, "ouble")) {
        if (tl_scheme_double_value (E, &d) < 0) {
          return tl_serialize_failf (C, E, "isn't of type 'double'");
        }
        if (isupper (name[0])) {
          if (tl_int_array_append (a, CODE_double) < 0) {
            return tl_serialize_failf (C, E, "output buffer overflow");
          }
        }
        if (tl_int_array_append_double (a, d) < 0) {
          return tl_serialize_failf (C, E, "output buffer overflow");
        }
        return 1;
      }
    break;
    case 'i':
      if (!strcmp (name + 1, "nt")) {
        if (tl_scheme_int_value (E, &i) < 0) {
          return tl_serialize_failf (C, E, "isn't of type 'int'");
        }
        if (isupper (name[0])) {
          if (tl_int_array_append (a, CODE_int) < 0) {
            return tl_serialize_failf (C, E, "output buffer overflow");
          }
        }
        if (tl_int_array_append (a, i) < 0) {
          return tl_serialize_failf (C, E, "output buffer overflow");
        }
        return 1;
      }
    break;
    case 'l':
      if (!strcmp (name + 1, "ong")) {
        if (tl_scheme_long_value (E, &l) < 0) {
          return tl_serialize_failf (C, E, "isn't of type 'long'");
        }
        if (isupper (name[0])) {
          if (tl_int_array_append (a, CODE_long) < 0) {
            return tl_serialize_failf (C, E, "output buffer overflow");
          }
        }
        if (tl_int_array_append_long (a, l) < 0) {
          return tl_serialize_failf (C, E, "output buffer overflow");
        }
        return 1;
      }
    break;
    case 's':
      if (!strcmp (name + 1, "tring")) {
        if (tl_scheme_string_value (E, &s) < 0) {
          return tl_serialize_failf (C, E, "isn't of type 'string'");
        }
        if (isupper (name[0])) {
          if (tl_int_array_append (a, CODE_string) < 0) {
            return tl_serialize_failf (C, E, "output buffer overflow");
          }
        }
        if (tl_int_array_append_string (a, s) < 0) {
          return tl_serialize_failf (C, E, "output buffer overflow");
        }
        return 1;
      }
    break;
  }

  return 0;
}