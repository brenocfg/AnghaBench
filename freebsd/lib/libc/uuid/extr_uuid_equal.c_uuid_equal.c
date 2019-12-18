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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int uuid_is_nil (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_s_ok ; 

int32_t
uuid_equal(const uuid_t *a, const uuid_t *b, uint32_t *status)
{

	if (status != NULL)
		*status = uuid_s_ok;

	/* Deal with equal or NULL pointers. */
	if (a == b)
		return (1);
	if (a == NULL)
		return (uuid_is_nil(b, NULL));
	if (b == NULL)
		return (uuid_is_nil(a, NULL));

	/* Do a byte for byte comparison. */
	return ((memcmp(a, b, sizeof(uuid_t))) ? 0 : 1);
}