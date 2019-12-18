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

/* Variables and functions */
 int RR_CE_SIZE ; 
 int /*<<< orphan*/  set_num_733 (unsigned char*,int) ; 

__attribute__((used)) static int
set_SUSP_CE(unsigned char *p, int location, int offset, int size)
{
	unsigned char *bp = p -1;
	/*  Extend the System Use Area
	 *   "CE" Format:
	 *               len  ver
	 *    +----+----+----+----+-----------+-----------+
	 *    | 'C'| 'E'| 1C | 01 | LOCATION1 | LOCATION2 |
	 *    +----+----+----+----+-----------+-----------+
	 *    0    1    2    3    4          12          20
	 *    +-----------+
	 *    | LOCATION3 |
	 *    +-----------+
	 *   20          28
	 *   LOCATION1 : Location of Continuation of System Use Area.
	 *   LOCATION2 : Offset to Start of Continuation.
	 *   LOCATION3 : Length of the Continuation.
	 */

	bp[1] = 'C';
	bp[2] = 'E';
	bp[3] = RR_CE_SIZE;	/* length	*/
	bp[4] = 1;		/* version	*/
	set_num_733(bp+5, location);
	set_num_733(bp+13, offset);
	set_num_733(bp+21, size);
	return (RR_CE_SIZE);
}