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
struct tl_token {int /*<<< orphan*/  text; struct tl_token* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (struct tl_token*,int) ; 

void tl_list_token_free (struct tl_token *L) {
  struct tl_token *E, *T;
  for (E = L; E != NULL; E = T) {
    T = E->next;
    cstr_free (&E->text);
    zfree (E, sizeof (*E));
  }
}