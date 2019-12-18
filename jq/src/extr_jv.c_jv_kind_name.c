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
typedef  int jv_kind ;

/* Variables and functions */
#define  JV_KIND_ARRAY 135 
#define  JV_KIND_FALSE 134 
#define  JV_KIND_INVALID 133 
#define  JV_KIND_NULL 132 
#define  JV_KIND_NUMBER 131 
#define  JV_KIND_OBJECT 130 
#define  JV_KIND_STRING 129 
#define  JV_KIND_TRUE 128 
 int /*<<< orphan*/  assert (int) ; 

const char* jv_kind_name(jv_kind k) {
  switch (k) {
  case JV_KIND_INVALID: return "<invalid>";
  case JV_KIND_NULL:    return "null";
  case JV_KIND_FALSE:   return "boolean";
  case JV_KIND_TRUE:    return "boolean";
  case JV_KIND_NUMBER:  return "number";
  case JV_KIND_STRING:  return "string";
  case JV_KIND_ARRAY:   return "array";
  case JV_KIND_OBJECT:  return "object";
  }
  assert(0 && "invalid kind");
  return "<unknown>";
}