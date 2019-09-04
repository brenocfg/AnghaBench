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
struct tl_expression {int magic; } ;
struct tl_compiler {int /*<<< orphan*/ * hm_magic; } ;

/* Variables and functions */
 struct tl_expression* tl_hashmap_get_f (int /*<<< orphan*/ *,struct tl_expression*,int /*<<< orphan*/ ) ; 

struct tl_expression *tl_expression_find_by_magic (struct tl_compiler *C, int magic) {
  int i;
  struct tl_expression T;
  T.magic = magic;
  for (i = 0; i < 2; i++) {
    struct tl_expression *E = tl_hashmap_get_f (&C->hm_magic[i], &T, 0);
    if (E) {
      return E;
    }
  }
  return NULL;
}