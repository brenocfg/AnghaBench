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
typedef  int /*<<< orphan*/  GUID ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ uuid_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline BOOLEAN
CompareGuid (const GUID *g1, const GUID *g2)
{
	uint32_t ignored_status;

	return (uuid_compare((const uuid_t *)g1, (const uuid_t *)g2,
	    &ignored_status) == 0);
}