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
struct vio_device_id {scalar_t__* compat; scalar_t__* type; } ;
struct vio_dev {char* type; char* compat; int compat_len; } ;

/* Variables and functions */
 scalar_t__ of_find_in_proplist (char const*,scalar_t__*,int) ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char const*) ; 

__attribute__((used)) static const struct vio_device_id *vio_match_device(
	const struct vio_device_id *matches,
	const struct vio_dev *dev)
{
	const char *type, *compat;
	int len;

	type = dev->type;
	compat = dev->compat;
	len = dev->compat_len;

	while (matches->type[0] || matches->compat[0]) {
		int match = 1;
		if (matches->type[0])
			match &= !strcmp(matches->type, type);

		if (matches->compat[0]) {
			match &= len &&
				of_find_in_proplist(compat, matches->compat, len);
		}
		if (match)
			return matches;
		matches++;
	}
	return NULL;
}