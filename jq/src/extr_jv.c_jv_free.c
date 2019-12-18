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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int JVP_KIND (int /*<<< orphan*/ ) ; 
#define  JV_KIND_ARRAY 132 
#define  JV_KIND_INVALID 131 
#define  JV_KIND_NUMBER 130 
#define  JV_KIND_OBJECT 129 
#define  JV_KIND_STRING 128 
 int /*<<< orphan*/  jvp_array_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_invalid_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_number_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_free (int /*<<< orphan*/ ) ; 

void jv_free(jv j) {
  switch(JVP_KIND(j)) {
    case JV_KIND_ARRAY:
      jvp_array_free(j);
      break;
    case JV_KIND_STRING:
      jvp_string_free(j);
      break;
    case JV_KIND_OBJECT:
      jvp_object_free(j);
      break;
    case JV_KIND_INVALID:
      jvp_invalid_free(j);
      break;
    case JV_KIND_NUMBER:
      jvp_number_free(j);
      break;
  }
}