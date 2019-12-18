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
struct tl_token {struct tl_token* next; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tl_token_polymorphic_match (struct tl_token *L, struct tl_token *R) {
  assert (L != NULL && R != NULL);
  if (strcmp (L->text, R->text)) {
    return 0;
  }
  while (L && R) {
    L = L->next;
    R = R->next;
  }
  return (L == NULL && R == NULL) ? 1 : 0;
}