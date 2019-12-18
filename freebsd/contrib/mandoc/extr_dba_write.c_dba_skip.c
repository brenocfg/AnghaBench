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
typedef  int /*<<< orphan*/  out ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dba_tell () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fwrite (scalar_t__ const**,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofp ; 

int32_t
dba_skip(int32_t nmemb, int32_t sz)
{
	const int32_t	 out[5] = {0, 0, 0, 0, 0};
	int32_t		 i, pos;

	assert(sz >= 0);
	assert(nmemb > 0);
	assert(nmemb <= 5);
	pos = dba_tell();
	for (i = 0; i < sz; i++)
		if (nmemb - fwrite(&out, sizeof(out[0]), nmemb, ofp))
			err(1, "fwrite");
	return pos;
}