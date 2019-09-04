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
struct tl_type {char* id; } ;

/* Variables and functions */
 char* mystrdup (char const*,int) ; 
 int /*<<< orphan*/  tl_type_tree ; 
 struct tl_type** tree_lookup_value_tl_type (int /*<<< orphan*/ ,struct tl_type*) ; 
 int /*<<< orphan*/  zfree (char*,int) ; 

struct tl_type *tl_get_type (const char *_id, int len) {
  char *id = mystrdup (_id, len);
  struct tl_type _t = {.id = id};
  struct tl_type **r = tree_lookup_value_tl_type (tl_type_tree, &_t);
  zfree (id, len + 1);
  return r ? *r : 0;
}