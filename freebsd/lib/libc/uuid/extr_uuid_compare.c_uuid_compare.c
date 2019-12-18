#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_RETURN (TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_seq_hi_and_reserved ; 
 int /*<<< orphan*/  clock_seq_low ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time_hi_and_version ; 
 int /*<<< orphan*/  time_low ; 
 int /*<<< orphan*/  time_mid ; 
 scalar_t__ uuid_is_nil (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_s_ok ; 

int32_t
uuid_compare(const uuid_t *a, const uuid_t *b, uint32_t *status)
{
	int	res;

	if (status != NULL)
		*status = uuid_s_ok;

	/* Deal with NULL or equal pointers. */
	if (a == b)
		return (0);
	if (a == NULL)
		return ((uuid_is_nil(b, NULL)) ? 0 : -1);
	if (b == NULL)
		return ((uuid_is_nil(a, NULL)) ? 0 : 1);

	/* We have to compare the hard way. */
	DIFF_RETURN(a, b, time_low);
	DIFF_RETURN(a, b, time_mid);
	DIFF_RETURN(a, b, time_hi_and_version);
	DIFF_RETURN(a, b, clock_seq_hi_and_reserved);
	DIFF_RETURN(a, b, clock_seq_low);

	res = memcmp(a->node, b->node, sizeof(a->node));
	if (res)
		return ((res < 0) ? -1 : 1);
	return (0);
}