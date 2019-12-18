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
struct data_key {int next_pn; int user; int /*<<< orphan*/  created_time; void* receives; void* transmits; } ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  os_get_time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee802_1x_kay_init_data_key(struct data_key *pkey)
{
	pkey->transmits = TRUE;
	pkey->receives = TRUE;
	os_get_time(&pkey->created_time);

	pkey->next_pn = 1;
	pkey->user = 1;
}