#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int tp; } ;
typedef  TYPE_1__ Tokenrow ;

/* Variables and functions */
 int /*<<< orphan*/  adjustrow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  makespace (TYPE_1__*) ; 
 int /*<<< orphan*/  movetokenrow (TYPE_1__*,TYPE_1__*) ; 
 int rowlen (TYPE_1__*) ; 

void
insertrow(Tokenrow *dtr, int ntok, Tokenrow *str)
{
	int nrtok = rowlen(str);

	dtr->tp += ntok;
	adjustrow(dtr, nrtok-ntok);
	dtr->tp -= ntok;
	movetokenrow(dtr, str);
	makespace(dtr);
	dtr->tp += nrtok;
	makespace(dtr);
}