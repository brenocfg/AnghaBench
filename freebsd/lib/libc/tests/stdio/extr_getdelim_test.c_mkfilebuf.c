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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _reader ; 
 int /*<<< orphan*/ * fropen (size_t*,int /*<<< orphan*/ ) ; 
 size_t* malloc (int) ; 

__attribute__((used)) static FILE *
mkfilebuf(void)
{
	size_t *offp;

	offp = malloc(sizeof(*offp));	/* XXX leak */
	*offp = 0;
	return (fropen(offp, _reader));
}