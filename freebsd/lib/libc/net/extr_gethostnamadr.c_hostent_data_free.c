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
struct hostent_data {scalar_t__ stayopen; } ;

/* Variables and functions */
 int /*<<< orphan*/  _endhosthtent (struct hostent_data*) ; 
 int /*<<< orphan*/  free (struct hostent_data*) ; 

__attribute__((used)) static void
hostent_data_free(void *ptr)
{
	struct hostent_data *hed = ptr;

	if (hed == NULL)
		return;
	hed->stayopen = 0;
	_endhosthtent(hed);
	free(hed);
}