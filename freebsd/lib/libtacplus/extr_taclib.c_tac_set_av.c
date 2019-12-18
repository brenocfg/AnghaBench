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
typedef  size_t u_int ;
struct tac_handle {int /*<<< orphan*/ * avs; } ;

/* Variables and functions */
 size_t MAXAVPAIRS ; 
 int save_str (struct tac_handle*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
tac_set_av(struct tac_handle *h, u_int index, const char *av)
{
	if (index >= MAXAVPAIRS)
		return -1;
	return save_str(h, &(h->avs[index]), av, av != NULL ? strlen(av) : 0);
}