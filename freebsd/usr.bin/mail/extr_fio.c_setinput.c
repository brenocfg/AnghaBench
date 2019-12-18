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
struct message {int /*<<< orphan*/  m_offset; int /*<<< orphan*/  m_block; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * itf ; 
 int /*<<< orphan*/  otf ; 
 int /*<<< orphan*/  positionof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FILE *
setinput(struct message *mp)
{

	(void)fflush(otf);
	if (fseeko(itf,
		   positionof(mp->m_block, mp->m_offset), SEEK_SET) < 0)
		err(1, "fseeko");
	return (itf);
}