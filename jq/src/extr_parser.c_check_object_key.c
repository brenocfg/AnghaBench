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
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  block_const (int /*<<< orphan*/ ) ; 
 scalar_t__ block_const_kind (int /*<<< orphan*/ ) ; 
 scalar_t__ block_is_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_dump_string_trunc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/  jv_kind_name (scalar_t__) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv check_object_key(block k) {
  if (block_is_const(k) && block_const_kind(k) != JV_KIND_STRING) {
    char errbuf[15];
    return jv_string_fmt("Cannot use %s (%s) as object key",
        jv_kind_name(block_const_kind(k)),
        jv_dump_string_trunc(block_const(k), errbuf, sizeof(errbuf)));
  }
  return jv_invalid();
}