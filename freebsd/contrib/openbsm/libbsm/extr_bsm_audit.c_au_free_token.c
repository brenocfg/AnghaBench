#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* t_data; } ;
typedef  TYPE_1__ token_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
au_free_token(token_t *tok)
{

	if (tok != NULL) {
		if (tok->t_data)
			free(tok->t_data);
		free(tok);
	}
}