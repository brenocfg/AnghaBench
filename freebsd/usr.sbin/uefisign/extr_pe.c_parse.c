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
struct mz_header {char* mz_signature; int /*<<< orphan*/  mz_lfanew; } ;
struct executable {scalar_t__ x_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 void parse_pe (struct executable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_check (struct executable*,int /*<<< orphan*/ ,int,char*) ; 

void
parse(struct executable *x)
{
	const struct mz_header *mz;

	range_check(x, 0, sizeof(*mz), "MZ header");

	mz = (struct mz_header *)x->x_buf;
	if (mz->mz_signature[0] != 'M' || mz->mz_signature[1] != 'Z')
		errx(1, "MZ header not found");

	return (parse_pe(x, mz->mz_lfanew));
}