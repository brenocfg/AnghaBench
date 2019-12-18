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
typedef  int u_int ;
struct interface {int dummy; } ;

/* Variables and functions */
 int NHASH_LEN ; 
 struct interface** nhash_tbl ; 

__attribute__((used)) static struct interface**
nhash(char *p)
{
	u_int i;

	for (i = 0; *p != '\0'; p++) {
		i = ((i<<1) & 0x7fffffff) | ((i>>31) & 1);
		i ^= *p;
	}
	return &nhash_tbl[i % NHASH_LEN];
}