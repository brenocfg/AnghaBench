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
typedef  int u_int32_t ;

/* Variables and functions */
 int HASH_MASK ; 
 int hash (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

u_int32_t hashkey(char *key)
{

	if (key == NULL)
		return (-1);
	return(hash((void *)key, strlen(key)) & HASH_MASK);
}