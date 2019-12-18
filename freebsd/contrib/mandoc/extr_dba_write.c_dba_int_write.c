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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  i ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofp ; 

void
dba_int_write(int32_t i)
{
	i = htobe32(i);
	if (fwrite(&i, sizeof(i), 1, ofp) != 1)
		err(1, "fwrite");
}