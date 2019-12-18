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
typedef  int daddr_t ;

/* Variables and functions */
 int drvread (int /*<<< orphan*/ *,void*,int,int) ; 
 int /*<<< orphan*/  dsk ; 

__attribute__((used)) static int
read_iso_block(void *buffer, daddr_t blkno)
{

	return (drvread(&dsk, buffer, blkno * 4, 4));
}