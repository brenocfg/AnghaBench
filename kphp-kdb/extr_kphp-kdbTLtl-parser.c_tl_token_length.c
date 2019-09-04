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
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tl_token_length (struct tl_token *T, int *tokens, int *total_length) {
  *tokens = *total_length = 0;
  while (T != NULL) {
    (*tokens)++;
    (*total_length) += strlen (T->text);
    T = T->next;
  }
}