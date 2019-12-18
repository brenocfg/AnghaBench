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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;

/* Variables and functions */
 int /*<<< orphan*/  NFDBITS ; 
 int /*<<< orphan*/  getdtablesize () ; 
 int howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 

void
zerofdset(fd_set *s)
{
  memset(s, '\0', howmany(getdtablesize(), NFDBITS) * sizeof (fd_mask));
}