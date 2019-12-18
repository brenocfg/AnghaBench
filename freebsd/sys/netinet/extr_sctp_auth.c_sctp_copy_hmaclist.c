#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_algo; int /*<<< orphan*/ * hmac; int /*<<< orphan*/  max_algo; } ;
typedef  TYPE_1__ sctp_hmaclist_t ;

/* Variables and functions */
 TYPE_1__* sctp_alloc_hmaclist (int /*<<< orphan*/ ) ; 

sctp_hmaclist_t *
sctp_copy_hmaclist(sctp_hmaclist_t *list)
{
	sctp_hmaclist_t *new_list;
	int i;

	if (list == NULL)
		return (NULL);
	/* get a new list */
	new_list = sctp_alloc_hmaclist(list->max_algo);
	if (new_list == NULL)
		return (NULL);
	/* copy it */
	new_list->max_algo = list->max_algo;
	new_list->num_algo = list->num_algo;
	for (i = 0; i < list->num_algo; i++)
		new_list->hmac[i] = list->hmac[i];
	return (new_list);
}