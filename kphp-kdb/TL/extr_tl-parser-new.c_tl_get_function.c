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
struct tl_constructor {char* id; } ;

/* Variables and functions */
 char* mystrdup (char const*,int) ; 
 int /*<<< orphan*/  tl_function_tree ; 
 struct tl_constructor** tree_lookup_value_tl_constructor (int /*<<< orphan*/ ,struct tl_constructor*) ; 
 int /*<<< orphan*/  zfree (char*,int) ; 

struct tl_constructor *tl_get_function (const char *_id, int len) {
  char *id = mystrdup (_id, len);
  struct tl_constructor _t = {.id = id};
  struct tl_constructor **r = tree_lookup_value_tl_constructor (tl_function_tree, &_t);
  zfree (id, len + 1);
  return r ? *r : 0;
}