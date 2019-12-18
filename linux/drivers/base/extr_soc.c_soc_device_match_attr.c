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
struct soc_device_attribute {scalar_t__ soc_id; scalar_t__ revision; scalar_t__ family; scalar_t__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  glob_match (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int soc_device_match_attr(const struct soc_device_attribute *attr,
				 const struct soc_device_attribute *match)
{
	if (match->machine &&
	    (!attr->machine || !glob_match(match->machine, attr->machine)))
		return 0;

	if (match->family &&
	    (!attr->family || !glob_match(match->family, attr->family)))
		return 0;

	if (match->revision &&
	    (!attr->revision || !glob_match(match->revision, attr->revision)))
		return 0;

	if (match->soc_id &&
	    (!attr->soc_id || !glob_match(match->soc_id, attr->soc_id)))
		return 0;

	return 1;
}