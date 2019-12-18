#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jblocks {int jb_off; } ;
struct TYPE_2__ {int d_bsize; } ;

/* Variables and functions */
 TYPE_1__ disk ; 

__attribute__((used)) static void
jblocks_advance(struct jblocks *jblocks, int bytes)
{

	jblocks->jb_off += bytes / disk.d_bsize;
}