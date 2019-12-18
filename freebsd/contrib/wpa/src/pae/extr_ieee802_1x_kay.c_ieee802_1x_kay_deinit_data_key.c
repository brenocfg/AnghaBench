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
struct data_key {int user; struct data_key* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct data_key*) ; 

__attribute__((used)) static void ieee802_1x_kay_deinit_data_key(struct data_key *pkey)
{
	if (!pkey)
		return;

	pkey->user--;
	if (pkey->user > 1)
		return;

	os_free(pkey->key);
	os_free(pkey);
}