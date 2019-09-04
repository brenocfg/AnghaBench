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
typedef  int /*<<< orphan*/  zval ;
struct tl_tree {int dummy; } ;
struct arg {int /*<<< orphan*/  type; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLUNI_NEXT ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

void *tluni_check_arg (void **IP, void **Data, zval **arr, struct tl_tree **vars) {
  struct arg *res = *(--Data);
  const char *id = *(IP ++);
  if (!id) {
    if (res->id) {  return 0; }
  } else {
    if (!res->id) {  return 0; }
    if (strcmp (id, res->id)) {  return 0; }
  }
  *(Data ++) = res->type;
  TLUNI_NEXT;
}