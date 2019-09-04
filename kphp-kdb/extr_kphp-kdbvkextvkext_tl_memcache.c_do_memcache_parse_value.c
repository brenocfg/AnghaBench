#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ data; void* len; } ;
struct TYPE_4__ {TYPE_1__ strval; int /*<<< orphan*/  lval; } ;
struct memcache_value {int type; TYPE_2__ val; void* flags; } ;

/* Variables and functions */
#define  MEMCACHE_ERROR 133 
#define  MEMCACHE_FALSE 132 
#define  MEMCACHE_TRUE 131 
#define  MEMCACHE_VALUE_LONG 130 
#define  MEMCACHE_VALUE_NOT_FOUND 129 
#define  MEMCACHE_VALUE_STRING 128 
 int /*<<< orphan*/  error_buf ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 void* strlen (scalar_t__) ; 
 int /*<<< orphan*/  tl_parse_end () ; 
 scalar_t__ tl_parse_error () ; 
 int /*<<< orphan*/  tl_parse_init () ; 
 void* tl_parse_int () ; 
 int /*<<< orphan*/  tl_parse_long () ; 
 void* tl_parse_string (scalar_t__*) ; 
 int /*<<< orphan*/  tl_set_error (int /*<<< orphan*/ ) ; 

struct memcache_value do_memcache_parse_value (void) {
  struct memcache_value value;
  tl_parse_init ();
  int x = tl_parse_int ();
  switch (x) {
  case MEMCACHE_VALUE_NOT_FOUND:
    value.type = MEMCACHE_VALUE_NOT_FOUND;
    break;
  case MEMCACHE_VALUE_LONG:
    value.type = MEMCACHE_VALUE_LONG;
    value.val.lval = tl_parse_long ();
    value.flags = tl_parse_int ();
    break;
  case MEMCACHE_VALUE_STRING:
    value.type = MEMCACHE_VALUE_STRING;
    value.val.strval.len = tl_parse_string (&value.val.strval.data);
    value.flags = tl_parse_int ();
    break;
  case MEMCACHE_ERROR:
    value.type = MEMCACHE_ERROR;
    tl_parse_long ();
    tl_parse_int ();
    value.val.strval.len = tl_parse_string (&value.val.strval.data);
    break;
  case MEMCACHE_TRUE:
    value.type = MEMCACHE_TRUE;
    break;
  case MEMCACHE_FALSE:
    value.type = MEMCACHE_FALSE;
    break;
  default:
    snprintf (error_buf, 1000, "Unknown magic %x", x);
    tl_set_error (error_buf);
    break;
  }
  tl_parse_end ();
  if (tl_parse_error ()) {
    value.type = MEMCACHE_ERROR;
    value.val.strval.data = tl_parse_error ();
    value.val.strval.len = strlen (value.val.strval.data);
  }
  return value;
}