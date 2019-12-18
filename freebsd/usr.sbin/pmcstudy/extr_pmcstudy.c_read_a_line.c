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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int pos; scalar_t__* vals; int /*<<< orphan*/  sum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* cnts ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int ncnts ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_a_line(FILE *io) 
{
	char buffer[8192], *p, *stop;	
	int pos, i;

	if (fgets(buffer, sizeof(buffer), io) == NULL) {
		return(0);
	}
	p = buffer;
	for (i=0; i<ncnts; i++) {
		pos = cnts[i].pos;
		cnts[i].vals[pos] = strtol(p, &stop, 0);
		cnts[i].pos++;
		cnts[i].sum += cnts[i].vals[pos];
		p = stop;
	}
	return (1);
}