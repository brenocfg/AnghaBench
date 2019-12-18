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
typedef  int /*<<< orphan*/  uint32_t ;
struct _region {int dummy; } ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  _region_head (struct _region*) ; 
 int _region_size (struct _region*) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
get32(struct _region *r, uint32_t *rval)
{

	if (_region_size(r) != 4)
		return (EFTYPE);

	memcpy(rval, _region_head(r), (size_t)4);
	*rval = be32toh(*rval);

	return (0);
}